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
  $form = array();

  $form['message'] = array(
    '#markup' => t('good to go'),
  );

  return $form;
}