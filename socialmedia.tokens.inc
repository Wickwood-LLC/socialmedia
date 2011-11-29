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
  
  $platforms = socialmedia_icon_platforms();
  foreach ($platforms AS $platform => $name) {
	  $tokens['socialmedia']['sm-' . $platform . '_icon-path:?'] = array(
	    'name' => t('@platform icon path', array('@platform' => $name)),
	    'description' => t("The path to the @platform icon", array('@platform' => $name)),
	  );
  }
  
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
      	list($platform_name, $hash) = explode('_', substr($name, 3));
      	// process icon paths
      	if (strpos($hash, 'icon-path') === 0) {
          $replacements[$original] = socialmedia_icon_tokens($platform_name, $hash);
      		continue;
      	}
      	$profile = NULL;      	
        if ((($type == 'user') || ($type == 'socialmedia')) && $uid) {
          $profile = socialmedia_account_load($platform_name, $uid);
        }
        if (($type == 'site') || (($type == 'socialmedia') && (!isset($profile['result']) || !$profile['result']))) {
          $profile = socialmedia_account_load($platform_name, 0);
        }
        $platform = socialmedia_platform_definition_load($platform_name);
dsm($platform_name);
dsm($platform);
        $replacement = call_user_func($platform['tokens callback'], $hash, $profile);
        if (!$replacement) {
dsm($platform);
			    $msg = t('You are trying to use a social media %platform profile token but the profile has not been set. !link',
			      array(
			        '%platform' => $platform['title'],
			        '!link' => l(t('Set @platform profile.', array('@platform' => $platform['title'])), 'admin/config/media/socialmedia')
			      )
			    );
			    widgets_set_error($data['widgets']['element'], $msg);
        }
        else {
        	$replacements[$original] = $replacement;
        }
      }
    }
  }
//dsm($replacements);
  return $replacements;
}

function socialmedia_icon_tokens($platform_name, $hash) {
  $b = explode(':', $hash);
  $iconsets = socialmedia_iconset_info();
  if (isset($b[1])) {
    $s = $b[1];
  }
  else {
    $s = variable_get('socialmedia_icon_default_style', '');
  }
  if (!$s) {
    $msg = t('You are trying to use a social media icon token but no default icon style has been set. !link',
      array(
        '!link' => l(t('Set default icon style.'), 'admin/config/media/socialmedia')
      )
    );
    widgets_data_error('set', $msg, 'warning', 'administer socialmedia');
    return '';
  }
  list($iconset, $style) = explode(':', $s);
  return base_path() . call_user_func($iconsets[$iconset]['path callback'], $platform_name, $style);	
}


