<?php
function socialmedia_socialmedia_platform_info() {
  $platforms = array();
  $platforms = array_merge($platforms, socialmedia_twitter_platform_info());
  $platforms = array_merge($platforms, socialmedia_facebook_platform_info());
  $platforms = array_merge($platforms, socialmedia_linkedin_platform_info());
  
  //$platforms = array_merge($platforms, socialmedia_addthis_platform_info());
 
  return $platforms;
}

function socialmedia_twitter_platform_info() {
  $platforms = array();
  $platforms['twitter'] = array(
    'title' => t('Twitter'),    
    //'description' => t('URL to your Twitter account'),
    'parser callback' => 'socialmedia_twitter_parser',
    'tokens callback' => 'socialmedia_twitter_tokens',
  ); 
  $platforms['twitter']['form'] = array(
    'title' => t('Twitter profile'),
    'description' => t('URL to your Twitter profile'),
  );
  $platforms['twitter']['tokens']['multi'] = array(
    'twitter_url' => array(
      'name' => t("Twitter account url"), 
      'description' => t("URL to twitter account."),
    ),
    'twitter_url-brief' => array(
      'name' => t("Twitter account url (brief)"), 
      'description' => t("URL to twitter account without protocol."),
    ), 
    'twitter_username' => array(
      'name' => t("Twitter username"), 
      'description' => t("Twitter account username"),
    ),   
    'twitter_amp-username' => array(
      'name' => t("Twitter @username"), 
      'description' => t("Twitter account username preceded by @"),
    ),
  );
  return $platforms;	
}

function socialmedia_twitter_parser($str) {
dsm($str);
  $pattern = '/http:\/\/(twitter\.com\/)(#!\/)?(\w+)+/i';
  //$pattern = '/^http:\/\/(www\.)?twitter\.com\/(#!\/)?(?<name>[^\/]+)(/\w+)*$/';
  if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    form_set_error('input_twitter', t('Twitter URL invalid.'));
    return FALSE;
  }
  $twitter = array();
  $twitter['url'] = $matches[1][0] . $matches[3][0];
  $twitter['title'] = $matches[3][0];
  
//dsm($matches);
  return $twitter;
}

function socialmedia_twitter_tokens($key, $profile) {
  switch ($key) {
  // Simple key values on the node.
    case 'url':
      return 'http://' . $profile['url'];
    case 'url-brief':
      return $profile['url'];
    case 'username':
      return $profile['title'];
    case 'amp-username':
      return '@' . $profile['title'];
  }
  return '';
}

function socialmedia_facebook_platform_info() {
  $platforms = array();
  $platforms['facebook'] = array(
    'title' => t('Facebook'),
    'description' => t('URL to your Facebook profile or page'),
    'parser callback' => 'socialmedia_facebook_parser',
    'tokens callback' => 'socialmedia_facebook_tokens',
  ); 
  $platforms['facebook']['form'] = array(
    'title' => t('Facebook profile'),
    'description' => t('URL to your Facebook profile'),
  );
  $platforms['facebook']['tokens']['multi'] = array(
    'facebook_url' => array(
      'name' => t("Facebook profile url"), 
      'description' => t("URL to Facebook profile."),
    ),
    'facebook_url-brief' => array(
      'name' => t("Facebook profile url (brief)"), 
      'description' => t("URL to Facebook profile without protocol."),
    ), 
    'facebook_username' => array(
      'name' => t("Facebook name"), 
      'description' => t("Facebook profile name"),
    ),   
  );
  return $platforms;  
}

function socialmedia_facebook_parser($str) {
//dsm($str);
  $pattern = '/http:\/\/(www\.)(facebook\.com\/)?(\w+)+/i';
  //$pattern = '/^http:\/\/(www\.)?twitter\.com\/(#!\/)?(?<name>[^\/]+)(/\w+)*$/';
  if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    form_set_error('input_facebook', t('Facebook URL invalid.'));
    return FALSE;
  }
  $profile = array();
  preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE);
  $a = explode('facebook.com/', $str);
  $b = explode('?', $a[1]);
  $c = explode('/', $b[0]);
  if(!isset($b[1]) && ($b[0] != 'profile.php')) {
    $profile['title'] = $b[0];
  }
  else if($b[0] == 'pages') {
    $profile['title'] = $b[1];
  }
  $profile['url'] = 'www.facebook.com/' . $a[1];
  
//dsm($matches);
  return $profile;
}

function socialmedia_facebook_tokens($key, $profile) {
//dsm($profile);
  switch ($key) {
  // Simple key values on the node.
    case 'url':
      return 'http://' . $profile['url'];
    case 'url-brief':
      return $profile['url'];
    case 'username':
      return $profile['title'];
  }
  return '';
}

function socialmedia_linkedin_platform_info() {
  $platforms = array();
  $platforms['linkedin'] = array(
    'title' => t('LinkedIn'),
    'description' => t('URL to your LinkedIn profile or page'),
    'parser callback' => 'socialmedia_linkedin_parser',
    'tokens callback' => 'socialmedia_linkedin_tokens',
  ); 
  $platforms['linkedin']['form'] = array(
    'title' => t('LinkedIn profile'),
    'description' => t('URL to your LinkedIn profile'),
  );
  $platforms['linkedin']['tokens']['multi'] = array(
    'linkedin_url' => array(
      'name' => t("LinkedIn profile url"), 
      'description' => t("URL to LinkedIn profile."),
    ),
    'linkedin_url-brief' => array(
      'name' => t("LinkedIn profile url (brief)"), 
      'description' => t("URL to LinkedIn profile without protocol."),
    ), 
    'linkedin_username' => array(
      'name' => t("LinkedIn name"), 
      'description' => t("LinkedIn profile name"),
    ),   
  );
  return $platforms;  
}

function socialmedia_linkedin_parser($str) {
//dsm($str);
  $pattern = '/http:\/\/(www\.)(linkedin\.com\/)?(\w+)+/i';
  //$pattern = '/^http:\/\/(www\.)?twitter\.com\/(#!\/)?(?<name>[^\/]+)(/\w+)*$/';
  if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    form_set_error('input_linkedin', t('LinkedIn URL invalid.'));
    return FALSE;
  }
  $profile = array();
  preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE);
  $a = explode('linkedin.com/', $str);
  $b = explode('?', $a[1]);
  $c = explode('/', $b[0]);
  if(!isset($b[1]) && ($b[0] != 'profile.php')) {
    $profile['title'] = $b[0];
  }
  else if($b[0] == 'pages') {
    $profile['title'] = $b[1];
  }
  $profile['url'] = 'www.linkedin.com/' . $a[1];
  
//dsm($matches);
  return $profile;
}

function socialmedia_linkedin_tokens($key, $profile) {
//dsm($profile);
  switch ($key) {
  // Simple key values on the node.
    case 'url':
      return 'http://' . $profile['url'];
    case 'url-brief':
      return $profile['url'];
    case 'username':
      return $profile['title'];
  }
  return '';
}

function socialmedia_addthis_platform_info() {
  $platforms = array();
  $platforms['addthis'] = array(
    'title' => t('AddThis'),
    'description' => t('Social sharing widgets.'),
  ); 
  $platforms['facebook']['form'] = array(
    'title' => t('AddThis username'),
    'description' => t('AddThis account username'),
  );
  $platforms['addthis']['tokens']['multi'] = array(
    'addthis_username' => array(
      'name' => t("AddThis username"), 
      'description' => t("Addthis"),
    ),   
  );
  return $platforms;  
}

