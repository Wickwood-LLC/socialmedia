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
  
  $form = array();
  
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