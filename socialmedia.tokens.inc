<?php

function socialmedia_token_info() {
  $type = array(
    'name' => t('Social media'), 
    'description' => t('Tokens related to social media sites.'), 
    //'needs-data' => 'socialmedia',
  );
  $tokens = array(
    'socialmedia' => array(),
    'site' => array(),
    'user' => array(), 
    'current-page' => array(), 
  );

  $profiles = socialmedia_platform_definitions();
  foreach ($profiles AS $platform => $data) {
    if (is_array($data['tokens'])) {
      foreach ($data['tokens'] AS $ttype => $tdata) {
        if($ttype == 'multi') {
          foreach($tdata AS $key => $ttdata) {
            $tokens['socialmedia']['sm-' . $key] = $ttdata;
            $tokens['site']['sm-' . $key] = $ttdata;
            $tokens['user']['sm-' . $key] = $ttdata;
          }
        }
        else {
          foreach($tdata AS $key => $ttdata) {
            $tokens[$ttype]['sm-' . $key] = $ttdata;
          }
        }
      } 
    }
  }
  /*
  // Core tokens for nodes.
  $socialmedia['twitter_account_url'] = array(
    'name' => t("Twitter account url"), 
    'description' => t("URL to twitter account."),
  );
  */
  
  $tokens['current-page']['title-plain'] = array(
    'name' => t('The title of the current page stripped of HTML'),
  );
  
  return array(
    'types' => array('socialmedia' => $type), 
    'tokens' => array(
      'socialmedia' => $tokens['socialmedia'],
      //'usersite' => $tokens['usersite'],
      'site' => $tokens['site'],
      'user' => $tokens['user'],
      'current-page' => $tokens['current-page'],
    ),
  );
}

function socialmedia_tokens($type, $tokens, array $data = array(), array $options = array()) {
//dsm($data);
//dsm($tokens);
//dsm($type);
  $replacements = array();
  if ($type == 'current-page') {
  	if (isset($tokens['title-plain'])) {
  		$replacements[$tokens['title-plain']] = strip_tags(drupal_get_title());
  	}
  }
  if (($type == 'site') || ($type == 'user') || ($type == 'socialmedia')) {
    $uid = (($type == 'user') && isset($data['user']->uid)) ? $data['user']->uid : 0; 
    foreach ($tokens as $name => $original) {     	
      if (strpos($name, 'sm-') === 0) {
      	$a = explode('_', substr($name, 3));
      	$platform_name = $a[0];
      	$hash = $a[1];
      	$profile = NULL;      	
        if ((($type == 'user') || ($type == 'socialmedia')) && $uid) {
          $profile = socialmedia_account_load($platform_name, $uid);
        }
        if (($type == 'site') || (($type == 'socialmedia') && (!isset($profile['result']) || !$profile['result']))) {
          $profile = socialmedia_account_load($platform_name, 0);
        }
        $platform = socialmedia_platform_definition_load($platform_name);
//dsm($platform_name);
//dsm($platform);
        $replacements[$original] = call_user_func($platform['tokens callback'], $hash, $profile);
      }
    }
  }
//dsm($replacements);
  return $replacements;
}


