<?php 

/*
 * Functions pertaining to iconset management
 */

function socialmedia_icon_style_options($for_widgets = TRUE, $platform = NULL) {
  $icons = socialmedia_iconset_info();
  $options = array();
  if ($for_widgets) {
    $options[] = t('Default');
  }
//dsm($icons);
  foreach ($icons AS $iconset_name => $iconset) {
    if (socialmedia_iconset_is_installed($iconset_name)) {
      foreach($iconset['styles'] AS $sid => $style) {
        if($for_widgets) {
          $options[$iconset['name']][base_path() . call_user_func($iconset['path callback'], $platform, $sid)] = $style;
        }
        else {
          $options[$iconset['name']][$iconset_name . ':' . $sid] = $style;
        }
      }       
    }
  }
//dsm($options);
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
    'googleplus' => t('Google+'),
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
    'instructions' => t('Copy the content of the <em>Vector Social Media Icons/PNG</em> directory in the download archive into the %directory.',
      array('%directory' => drupal_get_path('module', 'socialmedia') . '/icons/icondock/')
    )
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
  $icons['dryicons'] = array(
    'name' => 'dryicons',
    'styles' => array(
      '16x16' => '16x16',
      '24x24' => '24x24',
      '32x32' => '32x32',
      '48x48' => '48x48',
      '64x64' => '64x64', 
      '128x128' => '128x128', 
    ),
    'path callback' => 'socialmedia_icon_path_dryicons', 
    'download' => 'http://dryicons.com/free-icons/category/social/',
    'instructions' => t('Download the PNG version of all four sets. Copy the content of the <em>PNG</em> directory in the download archive into the %directory. Some directories are misnamed in set 2. Merge icons from folders ending in "px", e.g. 64x64px, into their non px equivalents, e.g. 64x64.',
      array('%directory' => drupal_get_path('module', 'socialmedia') . '/icons/dryicons/')
    )
  );
  return $icons;
}

function socialmedia_icon_path_dryicons($platform = 'twitter', $style = NULL) {
  $style = isset($style) ? $style : '32x32';
  $pt = array(
    'googleplus' => 'google_plus',
  );
  $path = drupal_get_path('module', 'socialmedia') . '/icons/dryicons/' . $style . '/' . ((isset($pt[$platform]))? $pt[$platform] : $platform) . '.png'; 
  return $path;
}

function socialmedia_icon_path_icondock($platform = 'twitter', $style = NULL) {
  $style = isset($style) ? $style : '32px';
  $t = array(
    'googleplus' => 'google-plus',
  );
  $path = drupal_get_path('module', 'socialmedia') . '/icons/icondock/' . $style . '/' . ((isset($t[$platform]))? $t[$platform] : $platform) . '.png'; 
  return $path;
}

function socialmedia_icon_path_thegforce($platform = 'twitter', $style = NULL) {
  $trans = array(
    'delicious' => 'Del icio us',
    'digg' => 'Digg',
    'facebook' => 'Facebook',
    'flickr' => 'Flickr',
    'google' => 'Google',
    'googleplus' => 'Google',
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
