<?php
// $Id$

/**
 * @file
 * Admin page callback for the socialmedia module.
 */

/**
 * Builds and returns the socialmedia settings form.
 */
function socialmedia_admin_settings() {
  drupal_add_css(drupal_get_path('module', 'socialmedia') . '/socialmedia.admin.css');
	
  $form = array();
  
  $form['platforms'] = array(
    '#type' => 'fieldset',
    '#title' => t('Platforms'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Select which social media platforms you want to enable on your site.'),
  ); 
  
  $platforms = socialmedia_socialmedia_platform_info();
  $options = array();
  foreach ($platforms AS $platform_name => $platform) {
  	$options[$platform_name] = $platform['title'];
  }
  $defaults = array_keys($options);
  $form['platforms']['socialmedia_platforms_site'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Site platforms'),
    '#default_value' => variable_get('socialmedia_platforms_site', $defaults),
    '#description' => t('Select the platforms you want active for site wide profiles.'),
    '#options' => $options,
    '#multicolumn' => array('width' => 2),  // multi colunms the checkboxes if multicolumnchecdkboxesradio.module installed
  );
  
  $form['platforms']['socialmedia_platforms_user'] = array(
    '#type' => 'checkboxes',
    '#title' => t('User platforms'),
    '#default_value' => variable_get('socialmedia_platforms_user', $defaults),
    '#description' => t('Select the platforms you want active for user level profiles. Only users with the !permissions permission will be able to add user profiles.',
      array(
        '!permissions' => l(t('Administer own profiles'), 'admin/people/permissions'),
      )
     ),
    '#options' => $options,
    '#multicolumn' => array('width' => 2),  // multi colunms the checkboxes if multicolumnchecdkboxesradio.module installed
  );
  
  $form['iconsets'] = array(
    '#type' => 'fieldset',
    '#title' => t('Icon sets'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $options = socialmedia_icon_style_options(FALSE);
  $form['iconsets']['socialmedia_icon_default_style'] = array(
    '#type' => 'select',
    '#title' => t('Default icon style'),
    '#default_value' => variable_get('socialmedia_icon_default_style', ''),
  //'#description' => t('The name is used in URLs for generated images. Use only lowercase alphanumeric characters, underscores (_), and hyphens (-).'),
    '#options' => $options,
  );
  
  $examples = socialmedia_icon_platforms();
  $header = array(t('Icon set'), t('Styles'));
  foreach ($examples AS $ekey => $ename) {
  	$header[] = '';
  }
  
  $rows = array();
  $icons = socialmedia_iconset_info();
  //$examples = array('twitter', 'facebook', 'stumbleupon', 'youtube');
  foreach ($icons AS $iconset_name => $iconset) {
//dsm($iconset);
    $row = array(
      $iconset['name'],
      implode('<br />', $iconset['styles']),
    );
    if (socialmedia_iconset_is_installed($iconset_name)) {
    	foreach ($examples AS $pkey => $pname) {
    		$vars = array(
    		  'path' => call_user_func($iconset['path callback'], $pkey),
    		  //'alt' => $pname,
    		  'title' => $pname,
    		);
    		$row[] = theme('image', $vars) . ' ';
    	}
    	
    }
    else {
    	$str = t('<strong>Not installed.</strong><br />To install: !download and install into %dir.',
    	  array(
    	    '!download' => l(t('download'), $iconset['download'], array('attributes' => array('target' => '_blank'))),
    	    '%dir' => drupal_get_path('module', 'socialmedia') . '/icons/' . $iconset_name . '/',
    	  )
    	);
    	if (isset($iconset['instructions'])) {
    	  $str .= ' ' . $iconset['instructions'];
    	}
    	$row[] = array(
    	  'data' => $str,
    	  'colspan' => count($examples),
    	);
    }
    $rows[] = $row;
    $vars = array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array(
        'id' => 'socialmedia-iconsets',
      ),
    );
	  $form['iconsets']['installed'] = array(
	    '#markup' => theme('table', $vars),
	  );    
  
  }
  
  //dsm($form);
  return system_settings_form($form);
}

/**
 * Builds and returns the socialmedia settings form.
 */
function socialmedia_admin_profiles_form($form, &$form_state, $context = 'site', $user = NULL) {
//dsm(func_get_args());
//dsm($user);
  $uid = (is_object($user)) ? $user->uid : 0;

  $platforms = socialmedia_platform_definitions();
  $defaults = array_keys($platforms);
//dsm($platforms);
//dsm($defaults);
  $active_platforms = variable_get('socialmedia_platforms_' . (($user) ? 'user' : 'site'), $defaults);
//dsm($active_platforms);
  foreach ($platforms AS $name => $platform) {
  	if (!$active_platforms[$name]) {
  		continue;
  	}
    $profile = socialmedia_profile_load($name, $uid);
//dsm($profile);
    $form['uid'] = array(
      '#type' => 'value',
      '#value' => $uid,
    );
	  $form[$name] = array(
	    '#type' => 'fieldset',
	    '#title' => $platform['title'],
	    '#collapsible' => TRUE,
	    '#collapsed' => FALSE,
	  );
	  $default_description = t('Enter the URL to your @platform profile.', array('@platform' => $platform['title']));
    $form[$name]['input_' . $name . '_url'] = array(
      '#type' => 'textfield',
      '#title' => $platform['title'] . ' URL',
      '#default_value' => (isset($profile['inputs']['url'])) ? $profile['inputs']['url'] : '',
      '#description' => isset($platform['profile url']) ? $platform['profile description url'] : $default_description,
      '#size' => 80,
    );
    $default_description = t('Enter your @platform profile name how you want it displayed in text links. Leave blank to use the username from the URL.', array('@platform' => $platform['title']));
    $form[$name]['input_' . $name . '_username'] = array(
      '#type' => 'textfield',
      '#title' => $platform['title'] . ' Username',
      '#default_value' => (isset($profile['inputs']['username'])) ? $profile['inputs']['username'] : '',
      '#description' => isset($platform['description username']) ? $platform['description username'] : $default_description,
      '#size' => 32,
    ); 
    /* 
    if ($profile) {
      $form[$name]['info_' . $name] = array(
        '#type' => 'markup',
        '#markup' => t('profile: ') . l($profile['title'], 'http://' . $profile['url']),
      );       
    }
    */
  }
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  
  //dsm($form);
  return $form;
}

function _socialmedia_admin_profiles_form_build_inputs($values, $platforms) {
  $inputs = array();
	foreach ($values AS $key => $value) {
    if (strpos($key, 'input_') === 0) {
      $key = substr($key, 6);
      foreach ($platforms AS $platform_name => $platform) {
        if (strpos($key, $platform_name . '_') === 0) {
          $key = substr($key, strlen($platform_name . '_'));
          if (!isset($inputs[$platform_name])) {
          	$inputs[$platform_name] = array();
          }
          $inputs[$platform_name][$key] = $value;
        }
      }
    }
	}	
  return $inputs;
}

function socialmedia_admin_profiles_form_validate($form, &$form_state) {

	$platforms = socialmedia_platform_definitions('site');
	$inputs = _socialmedia_admin_profiles_form_build_inputs($form_state['values'], $platforms);
//dsm($inputs);
	foreach ($platforms AS $platform_name => $platform) {
		if (!isset($inputs[$platform_name])) {
			continue;
		}
		if (isset($platform['parser callback'])) {
			call_user_func($platform['parser callback'], $inputs[$platform_name]);
		}
	}	
}

function socialmedia_admin_profiles_form_submit($form, &$form_state) {
  $platforms = socialmedia_platform_definitions();
  $inputs = _socialmedia_admin_profiles_form_build_inputs($form_state['values'], $platforms);
  foreach ($platforms AS $platform_name => $platform) {
    if (!isset($inputs[$platform_name])) {
      continue;
    }
    if (isset($platform['parser callback'])) {    	
      $profile = call_user_func($platform['parser callback'], $inputs[$platform_name]);
      $profile['inputs'] = $inputs[$platform_name];
//dsm($profile);
      socialmedia_profile_save($profile, $platform_name, $form_state['values']['uid']);
    }
  }
	
  //$twitter = socialmedia_parse_twitter_profile($form_state['values']['socialmedia_profile_url_twitter']);
  //socialmedia_profile_save($twitter, 'twitter');

  return 'OK';
}