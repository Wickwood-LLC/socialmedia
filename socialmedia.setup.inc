<?php
// $Id$

/**
 * @file
 * Admin page callback for the socialmedia module.
 */

/*
 * TODO: finish wizard
 */
function socialmedia_admin_setup($step = 1) {
  if (!$step) {
    $step = 1;
  }
  $output = render(drupal_get_form('socialmedia_setup_' . $step .'_form'));
  return $output;
}

/** 
 * Checks if dependencies are installed
 * @param $form
 * @param $form_state
 */
function socialmedia_admin_setup_1_form($form, &$form_state) {
  $form = array();
  $output = '';
  
  if (!module_exists('widgets')) {
    $output = t('In order to setup Social media you need to !install.',
      array('!install' => l(t('install the Widgets module'), 'admin/modules'))
    );
  }
  else {
    drupal_goto('admin/config/media/socialmedia/setup/2');
  }
  
  return $form;
}
/**
 * Select social media profiles
 * @param $form
 * @param $form_state
 */
function socialmedia_setup_2_form($form, $form_state) {
  require_once(drupal_get_path('module', 'socialmedia') . '/socialmedia.admin.inc');
  drupal_set_title(t('Social media profiles setup'));
  $instructions = <<<EOF
<p>The first step is to setup your social media profiles. The social media module supports several platforms such as Twitter, Facebook and Google+. If you already have accounts enter them below. If you have not setup any social media profiles yet or want to create additional ones, follow the homepage links below to create accounts. 
</p><p>
You do not have to create an account on all platforms. Any platforms that you do not enter a profile url for will be ignored. You can add and remove profiles later on the Social Media configuration page.  
EOF;
  $form['instructions'] = array(
    '#markup' => t($instructions),
  ); 
  $form['setup_mode'] = array(
    '#type' => 'value',
    '#value' => 1,
  );
  $fields = socialmedia_admin_profiles_form($form, $form_state, 'site', NULL, TRUE);

  unset($fields['Widget platforms']);
  $form = array_merge($form, $fields);
  $form['#validate'][] = 'socialmedia_admin_profiles_form_validate';
  $form['#submit'][] = 'socialmedia_setup_2_form_submit';

  return $form;
}

function socialmedia_setup_2_form_submit($form, $form_state) {
  $values = $form_state['values'];
//dsm($values);
  $platforms = socialmedia_socialmedia_platform_info();
  $platforms_site = variable_get('socialmedia_platforms_site' , array());
  foreach ($platforms AS $key => $platform) {
    if (!isset($values['input_' . $key . '_url'])) {
      continue;
    }
    $platforms_site[$key] = $key;
    if (!trim($values['input_' . $key . '_url'])) {
      $platforms_site[$key] = 0;
      unset($form_state['values']['input_' . $key . '_url']);
      unset($form_state['values']['input_' . $key . '_username']);
    }
    //unset($values
  }
  variable_set('socialmedia_platforms_site', $platforms_site, array());
//dsm($platforms_site);
  $inputs = _socialmedia_admin_profiles_form_build_inputs($form_state['values'], $platforms);
//dsm($inputs);
  // save profile data
  socialmedia_admin_profiles_form_submit($form, $form_state);

  // clear widgets set cache so profile_default updates
  cache_clear_all('widgets_sets', 'cache');
  return 'OK';
}

function socialmedia_setup_3_form($form, $form_state) {
  $form =  array();
  $set = widgets_set_load('socialmedia_share-default');
  $form['preview'] = array(
    '#type' => 'item',
    '#title' => t('Preview'),
    '#markup' => theme('widgets_set_view', array('set' => $set)),
  );
  return $form; 
}