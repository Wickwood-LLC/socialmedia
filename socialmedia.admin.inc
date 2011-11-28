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
  
  $form['iconsets'] = array(
    '#type' => 'fieldset',
    '#title' => t('Icon sets'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $options = socialmedia_icon_style_options();
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
dsm($iconset);
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
    	$str = t('<strong>Not installed.</strong><br />To install: !download and install into %dir',
    	  array(
    	    '!download' => l(t('download'), $iconset['download'], array('attributes' => array('target' => '_blank'))),
    	    '%dir' => drupal_get_path('module', 'socialmedia') . '/icons/' . $iconset_name . '/',
    	  )
    	);
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
function socialmedia_admin_accounts_form() {
  $form['platforms'] = array(
    '#type' => 'fieldset',
    '#title' => t('Platforms'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $platforms = socialmedia_platform_definitions();
//dsm($platforms);
  foreach ($platforms AS $name => $platform) {
    $account = socialmedia_account_load($name);
//dsm($account);
    $form['platforms']['input_' . $name] = array(
      '#type' => 'textfield',
      '#title' => $platform['title'],
      '#default_value' => ($account) ? $account['input'] : '',
      '#description' => isset($platform['description']) ? $platform['description'] : '',
    ); 
    if ($account) {
      $form['platforms']['info_' . $name] = array(
        '#type' => 'markup',
        '#markup' => t('account: ') . l($account['title'], 'http://' . $account['url']),
      );       
    }
  }
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  
  //dsm($form);
  return $form;
}

function socialmedia_admin_accounts_form_validate($form, &$form_state) {
//dsm($form_state);
	$platforms = socialmedia_platform_definitions();
//dsm($platforms);
	foreach ($platforms AS $name => $platform) {
		if (isset($platform['parser callback'])) {
			call_user_func($platform['parser callback'], $form_state['values']['input_' . $name]);
		}
	}
	
}

function socialmedia_admin_accounts_form_submit($form, &$form_state) {
	
 $platforms = socialmedia_platform_definitions();
  foreach ($platforms AS $name => $platform) {
    if (isset($platform['parser callback'])) {
      $profile = call_user_func($platform['parser callback'], $form_state['values']['input_' . $name]);
      $profile['input'] = $form_state['values']['input_' . $name];
      socialmedia_account_save($profile, $name);
    }
  }
	
  //$twitter = socialmedia_parse_twitter_account($form_state['values']['socialmedia_account_url_twitter']);
  //socialmedia_account_save($twitter, 'twitter');

  return 'OK';
}