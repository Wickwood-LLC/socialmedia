<?php
function socialmedia_socialmedia_platform_info() {
  $platforms = array();
  $platforms = array_merge($platforms, socialmedia_twitter_platform_info());
  $platforms = array_merge($platforms, socialmedia_facebook_platform_info());
  
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
  $platforms['twitter']['tokens']['socialmedia'] = array(
    'twitter_icon-path' => array(
      'name' => t("Twitter icon path"), 
      'description' => t("File path to twitter icon"),
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
  $platforms['facebook']['tokens']['socialmedia'] = array(
    'facebook_icon-path' => array(
      'name' => t("Facebook icon path"), 
      'description' => t("File path to facebook icon"),
    ),
  );  
  return $platforms;  
}

function socialmedia_facebook_parser($str) {
//dsm($str);
  $pattern = '/http:\/\/(www\.)(facebook\.com\/)?(\w+)+/i';
  //$pattern = '/^http:\/\/(www\.)?twitter\.com\/(#!\/)?(?<name>[^\/]+)(/\w+)*$/';
  if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    form_set_error('input_twitter', t('Twitter URL invalid.'));
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

function socialmedia_icon_style_options($platform = NULL) {
	$icons = socialmedia_iconset_info();
	$options = array();
	foreach ($icons AS $iconset_name => $iconset) {
		if (!$platform) {
			if (socialmedia_iconset_is_installed($iconset_name)) {
				$options[$iconset['name']] = $iconset['styles'];
			}
		}
	}
	return $options;
}

function socialmedia_iconset_is_installed($iconset) {
	return is_dir(drupal_get_path('module', 'socialmedia') . '/icons/' . $iconset );
}

function socialmedia_icon_platforms() {
	$platforms = array( 
	  'digg' => t('Digg'), 
	  'delicious' => t('Del.icio.us'),
	  'email' => t('E-mail'),  
	  'facebook' => t('Facebook'),
	  'flickr' => t('Flikr'),
	  'google' => t('Google'),
	  'google-plus' => t('Google+'),
	  'linkedin' => t('LinkedIn'),
	  'myspace' => t('MySpace'),
	  'pinterest' => t('Pinterest'),
	  'reddit' => t('Reddit'),
	  'rss' => t('RSS'),
	  'slideshare' => t('Slideshare'),
	  'stumbleupon' => t('StumbleUpon'),
	  'technorati' => t('Technorati'),
	  'twitter' => t('Twitter'),
	  'vimeo' => t('Vimeo'),
	  'youtube' => t('YouTube'),
	);
	return $platforms;
}

function socialmedia_iconset_info() {
  $icons['icondock'] = array(
    'name' => 'Icon Dock',
    'styles' => array(
      '16px' => '16x16',
      '24px' => '24x24',
      '32px' => '32x32',  
    ),
    'path callback' => 'socialmedia_icon_path_icondock', 
    'download' => 'http://icondock.com/free/vector-social-media-icons',
  );
  $icons['sada'] = array(
    'name' => 'Sada',
    'styles' => array(
      '16x16' => '16x16',
      '32x32' => '32x32',
      '64x64' => '64x64',  
    ),
    'path callback' => 'socialmedia_icon_path_sada', 
    'download' => 'http://www.profimagazin.cz/ikony/socialni-ikony-vcetne-ceskych-linkovacich-sluzeb-ke-stazeni-zdarma',
  );
  $icons['theg-force'] = array(
    'name' => 'TheG-Force',
    'styles' => array(
      '24x24' => '24x24',
      '32x32' => '32x32',
      '48x48' => '48x48',
      '64x64' => '64x64',  
    ),
    'path callback' => 'socialmedia_icon_path_thegforce', 
    'download' => 'http://theg-force.deviantart.com/art/Social-Icons-hand-drawned-109467069',
  );
  return $icons;
}

function socialmedia_icon_path_icondock($platform = 'twitter', $style = NULL) {
	$style = isset($style) ? $style : '32px';
	$path = drupal_get_path('module', 'socialmedia') . '/icons/icondock/' . $style . '/' . $platform . '.png'; 
	return $path;
}

function socialmedia_icon_path_sada($platform = 'twitter', $style = NULL) {
  $style = isset($style) ? $style : '32x32';
  $path = drupal_get_path('module', 'socialmedia') . '/icons/sada/' . $style . '/' . $platform . '.png'; 
  return $path;
}

function socialmedia_icon_path_thegforce($platform = 'twitter', $style = NULL) {
	$trans = array(
	  'delicious' => 'Del icio us',
	  'digg' => 'Digg',
	  'facebook' => 'Facebook',
	  'flickr' => 'Flickr',
	  'google' => 'Google',
	  'linkedin' => 'Linkedin',
	  'myspace' => 'Myspace',
	  'reddit' => 'Reddit',
	  'rss' => 'RSS',	  
	  'stumbleupon' => 'StumbleUpon',
	  'technorati' => 'Technorati',
	  'twitter' => 'Twitter',
	  'vimeo' => 'Vimeo',
	  'youtube' => 'Youtube',
	);
	if(!isset($trans[$platform])) {
		return FALSE;
	}
  $style = isset($style) ? $style : '32x32';
  $path = drupal_get_path('module', 'socialmedia') . '/icons/theg-force/' . $trans[$platform] . '/' . $style . '.png'; 
  return $path;
}