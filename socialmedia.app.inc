<?php
/**
* Implements hook_apps_app_info().
*/
function socialmedia_apps_app_info() {
  return array(
    'configure form' => 'socialmedia_apps_app_configure_form',
    //'demo content module' => 'enterprise_blog_content',
  );
}

function socialmedia_apps_app_configure_form() {
  $form = render(drupal_get_form('socialmedia_setup_1_form'));
  $form['#submit'] = 'socialmedia_setup_1_form_submit';

  return $form;
}