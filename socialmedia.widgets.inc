<?php

/**
 * @file
 * Functions needed to execute image elements provided by Image module.
 */

/**
 * Implements hook_widgets_element_info().
 */
function socialmedia_widgets_element_info() {
  $facebook_js_sdk = <<<EOF
<script>if(window.FB){ window.FB = null ;}//eat this !</script>
<div id="fb-root"></div>
<script>(function(d, s, id) {
  var js, fjs = d.getElementsByTagName(s)[0];
  if (d.getElementById(id)) {return;}
  js = d.createElement(s); js.id = id;
  js.src = "//connect.facebook.net/en_US/all.js#xfbml=1&appId=223324211035941";
  fjs.parentNode.insertBefore(js, fjs);
}(document, 'script', 'facebook-jssdk'));</script>
EOF;
  //$addthis_js = '<script type="text/javascript" src="http://s7.addthis.com/js/250/addthis_widget.js#username=[?addthis_username:[socialmedia:addthis:username]]"></script>';
  $addthis_js = '<script type="text/javascript" src="http://s7.addthis.com/js/250/addthis_widget.js#username=tomdude48"></script>';
    
  
  $elements = array(
    'socialmedia_twitter-tweet-no-count' => array(
      'label' => t('Twitter tweet button (no count)'),
      'help' => t('Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.'),
      'group' => t('Social media: Twitter'),
      'template' => '<a href="https://twitter.com/share" class="twitter-share-button" data-count="none">Tweet</a><script type="text/javascript" src="//platform.twitter.com/widgets.js"></script>',
      //'form callback' => 'widgets_template_auto_form',
    ), 
    'socialmedia_twitter-tweet-horizontal-count' => array(
      'label' => t('Twitter tweet button with horizontal count'),
      'help' => t('Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.'),
      'group' => t('Social media: Twitter'),
      'template' => '<a href="https://twitter.com/share" class="twitter-share-button" data-count="horizontal">Tweet</a><script type="text/javascript" src="//platform.twitter.com/widgets.js"></script>',
          //'form callback' => 'widgets_template_auto_form',
    ), 
// Facebook widgets
    'socialmedia_facebook-like-box' => array(
      'label' => t('Facebook like box'),
      'help' => t('Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.'),
      'group' => t('Social media: Facebook'),
      'template' => '<div class="fb-like-box" data-href="[?href=[socialmedia:sm-facebook_url]?]" data-width="[?width=[socialmedia:sm-default_width]?]" data-show-faces="[?show_faces=true?]" data-stream="[?data_stream=false?]" data-header="[?data_header=false?]"></div>',
      'add_js' => array(
        'data' => $facebook_js_sdk,
        'options' => array(
          'scope' => 'set_pre', 
          'type' => 'inline'
        ),
      ),
      'form callback' => 'widgets_template_auto_form',
    ),
// AddThis widgets
    'socialmedia_addthis-tweet' => array(
      'label' => t('Addthis tweet button'),
      'help' => t('Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.'),
      'group' => t('Social media: Twitter'),
      'template' => '<a class="addthis_button_tweet"[?count=?]tw:related="tutrtv:Tutr.tv" tw:via="[?via=[socialmedia:sm-twitter_username]?]"></a>',
      'add_js' => array(
        'data' => $addthis_js,
        'options' => array(
          'scope' => 'set_post', 
        ),
      ),
      'form callback' => 'socialmedia_widgets_addthis_tweet_form',
    ),
    'socialmedia_addthis-facebook-like' => array(
      'label' => t('AddThis Facebook like button'),
      'help' => t('Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.'),
      'group' => t('Social media: Facebook'),
      'template' => '<a class="addthis_button_facebook_like"[?layout=?] fb:like:width="450" fb:like:show_faces="true"></a>',
      'add_js' => array(
        'data' => $addthis_js,
        'options' => array(
          'scope' => 'set_post', 
        ),
      ),
      'form callback' => 'socialmedia_widgets_addthis_facebook_like_form',
    ),
    'socialmedia_addthis-facebook-send' => array(
      'label' => t('AddThis Facebook send button'),
      'help' => t('Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.'),
      'group' => t('Social media: Facebook'),
      'template' => '<a class="addthis_button_facebook_like"[?layout=?]></a>',
      'add_js' => array(
        'data' => $addthis_js,
        'options' => array(
          'scope' => 'set_post', 
        ),
      ),
      'form callback' => 'socialmedia_widgets_addthis_facebook_send_form',
    ),
    'socialmedia_addthis-google-plusone' => array(
      'label' => t('AddThis Google +1 button'),
      'help' => t('Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.'),
      'group' => t('Social media: Google+'),
      'template' => '<a class="addthis_button_google_plusone"[?size=?]></a>',
      'add_js' => array(
        'data' => $addthis_js,
        'options' => array(
          'scope' => 'set_post', 
        ),
      ),
      'form callback' => 'socialmedia_widgets_addthis_google_plusone_form',
    ),
    'socialmedia_addthis-stumbleupon' => array(
      'label' => t('AddThis StumbleUpon Badge'),
      'help' => t('Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.'),
      'group' => t('Social media: StumbleUpon'),
      'template' => '<a class="addthis_button_stumbleupon_badge"[?style=?]&su:bdg:url=[current-page:url]></a>',
      'add_js' => array(
        'data' => $addthis_js,
        'options' => array(
          'scope' => 'set_post', 
        ),
      ),
      'form callback' => 'socialmedia_widgets_addthis_stumbleupon_form',
    ),
    'socialmedia_addthis-addthis-counter' => array(
      'label' => t('AddThis Counter'),
      'help' => t('Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.'),
      'group' => t('Social media: Multi'),
      'template' => '<a class="addthis_counter"[?style=?]></a>',
      'add_js' => array(
        'data' => $addthis_js,
        'options' => array(
          'scope' => 'set_post', 
        ),
      ),
      'form callback' => 'socialmedia_widgets_addthis_addthis_counter_form',
    ),
  );
  
  $template = <<<EOF
<script src="http://widgets.twimg.com/j/2/widget.js"></script>
<script>
new TWTR.Widget({
  version: 2,
  type: 'profile',
  rpp: 4,
  interval: 30000,
  width: [?width=[socialmedia:sm-default_width]?],
  height: [?height=[socialmedia:sm-default_height]?],
  theme: {
    shell: {
      background: '[?shell_background_color=[socialmedia:sm-default_color_header_background]?]',
      color: '[?shell_text_color=[socialmedia:sm-default_color_header_text]?]'
    },
    tweets: {
      background: '[?tweets_background_color=[socialmedia:sm-default_color_body_background]?]',
      color: '[?tweets_text_color=[socialmedia:sm-default_color_body_text]?]',
      links: '[?shell_link_color=[socialmedia:sm-default_color_body_linktext]?]'
    }
  },
  features: {
    scrollbar: false,
    loop: false,
    live: false,
    behavior: 'all'
  }
}).render().setUser('[?profile=[socialmedia:sm-twitter_username]?]').start();
</script>  
EOF;
  $elements['socialmedia_twitter-profile-widget'] = array(
    'label' => t('Twitter profile widget'),
    'group' => t('Social media: Twitter'),
    'template' => $template,
    'form callback' => 'widgets_template_auto_form',
  );
  
  
  
  $elements = array_merge($elements, socialmedia_share_platforms_info());
  
//dsm($elements);

  return $elements;
}

function socialmedia_share_platforms_info() {
  $platforms = socialmedia_share_platforms();
  $elements = array();
  $labelpost = array(
    'profile-url' => t('profile url'),
    'profile-text-link' => t('profile text link'),
    'profile-button' => t('profile button'),    
    'share-text-link' => t('share text link'),
    'share-button' => t('share button'),
  );
  foreach ($platforms AS $platform_name => $platform) {
    foreach ($platform['templates'] AS $template_name => $template) {
      $lin = 
      $elements['socialmedia_socialmedia-' . $platform_name . '-' . $template_name] = array(
        'platform' => $platform_name,
        'label' => t('Socialmedia @platform @type', 
          array(
            '@platform' => $platform['label'],
            '@type' => $labelpost[$template_name],
          )),
        //'help' => t('Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.'),
        'group' => $platform['group'],
        'template' => $template,
        //'form callback' => 'socialmedia_widgets_share_platforms_form',
      );
      // add form callback if fields
      if($template_name != 'share-text-link') {
        $elements['socialmedia_socialmedia-' . $platform_name . '-' . $template_name]['form callback'] = 'socialmedia_widgets_share_platforms_form';
      }
    }
  }
  return $elements;
}

function socialmedia_share_platforms() {
  $platforms = array();
  $platforms['twitter'] = array(
    'label' => t('Twitter'),
    'group' => t('Social media: Twitter'),
  );
  $platforms['twitter']['templates'] = array(
    'profile-url' => "[?profile_url=[socialmedia:sm-twitter_url]?]",
    'profile-text-link' => '<a href="http://twitter.com/[?profile_username=[socialmedia:sm-twitter_username]?]" title="Visit [?profile_username=[socialmedia:sm-twitter_amp-username]?] on Twitter">[?profile_username=[socialmedia:sm-twitter_amp-username]?]</a>',  
    'profile-button' => '<a href="http://twitter.com/[?profile_username=[socialmedia:sm-twitter_username]?]" title="Visit [?profile_username=[socialmedia:sm-twitter_amp-username]?] on Twitter"><img src="[?icon-path=[socialmedia:sm-twitter_icon-path]?]" alt="Twitter icon" ></a>',
    'share-text-link' => '<a href="http://twitter.com/share?url=[current-page:url]&text=[current-page:title-plain]" title="Tweet this">[?link-text=Tweet?]</a>',
    'share-button' => '<a href="http://twitter.com/share?url=[current-page:url]&text=[current-page:title-plain]" title="Tweet this"><img src="[?icon-path=[socialmedia:sm-twitter_icon-path]?]" alt="Twitter icon" ></a>',
  );
  
  $platforms['facebook'] = array(
    'label' => t('Facebook'),
    'group' => t('Social media: Facebook'),
  );
  $platforms['facebook']['templates'] = array(
    'profile-url' => "[?profile_url=[socialmedia:sm-facebook_url]?]",
    'profile-text-link' => '<a href="[?profile_url=[socialmedia:sm-facebook_url]?]" title="Visit [?profile_username=[socialmedia:sm-facebook_username]?] on Facebook">[?profile_username=[socialmedia:sm-facebook_username]?]</a>',  
    'profile-button' => '<a href="[?profile_url=[socialmedia:sm-facebook_url]?]" title="Visit [?profile_username=[socialmedia:sm-facebook_username]?] on Facebook"><img src="[?icon-path=[socialmedia:sm-facebook_icon-path]?]" alt="Facebook icon" ></a>',
    'share-text-link' => '<a href="http://www.facebook.com/sharer.php?u=[current-page:url]&t=[current-page:title-plain]" title="[?link-text=Share on Facebook?]">[?link-text=Share on Facebook?]</a>',
    'share-button' => '<a href="http://www.facebook.com/sharer.php?u=[current-page:url]&t=[current-page:title-plain]" title="Share on Facebook"><img src="[?icon-path=[socialmedia:sm-facebook_icon-path]?]" alt="Facebook icon" ></a>',
  );
  
  $platforms['flickr'] = array(
    'label' => t('Flickr'),
    'group' => t('Social media: Flickr'),
  );
  $platforms['flickr']['templates'] = array(
    'profile-url' => "[?profile_url=[socialmedia:sm-flickr_url]?]",
    'profile-text-link' => '<a href="[?profile_url=[socialmedia:sm-flickr_url]?]" title="Visit [?profile_username=[socialmedia:sm-flickr_username]?] on Flickr">[?profile_username=[socialmedia:sm-flickr_username]?]</a>',  
    'profile-button' => '<a href="[?profile_url=[socialmedia:sm-flickr_url]?]" title="Visit [?profile_username=[socialmedia:sm-flickr_username]?] on Flickr"><img src="[?icon-path=[socialmedia:sm-flickr_icon-path]?]" alt="Flickr icon" ></a>',
  );
  
  $platforms['googleplus'] = array(
    'label' => t('Google+'),
    'group' => t('Social media: Google+'),
  );
  $platforms['googleplus']['templates'] = array(
    'profile-url' => "[?profile_url=[socialmedia:sm-googleplus_url]?]",
    'profile-text-link' => '<a href="[?profile_url=[socialmedia:sm-googleplus_url]?]" title="Visit [?profile_username=[socialmedia:sm-googleplus_username]?] on Google+">[?profile_username=[socialmedia:sm-googleplus_username]?]</a>',  
    'profile-button' => '<a href="[?profile_url=[socialmedia:sm-googleplus_url]?]" title="Visit [?profile_username=[socialmedia:sm-googleplus_username]?] on Google+"><img src="[?icon-path=[socialmedia:sm-googleplus_icon-path]?]" alt="Google+ icon" ></a>',
  );
  
  $platforms['linkedin'] = array(
    'label' => t('LinkedIn'),
    'group' => t('Social media: LinkedIn'),
  );
  $platforms['linkedin']['templates'] = array(
    'profile-url' => "[?profile_url=[socialmedia:sm-linkedin_url]?]",
    'profile-text-link' => '<a href="[?profile_url=[socialmedia:sm-linkedin_url]?]" title="Visit [?profile_username=[socialmedia:sm-linkedin_username]?] on LinkedIn">[?profile_username=[socialmedia:sm-linkedin_username]?]</a>',  
    'profile-button' => '<a href="[?profile_url=[socialmedia:sm-linkedin_url]?]" title="Visit [?profile_username=[socialmedia:sm-linkedin_username]?] on LinkedIn"><img src="[?icon-path=[socialmedia:sm-linkedin_icon-path]?]" alt="LinkedIn icon" ></a>',
    'share-text-link' => '<a href="http://www.linkedin.com/shareArticle?mini=true&url=[current-page:url]&title=[current-page:title-plain]&source=' . $_SERVER['HTTP_HOST'] . '" title="[?link-text=Share on LinkedIn?]">[?link-text=Share on LinkedIn?]</a>',
    'share-button' => '<a href="http://twitter.com/share?url=[current-page:url]&text=[current-page:title-plain]" title="Tweet this"><img src="[?icon-path=[socialmedia:sm-twitter_icon-path]?]" alt="Twitter icon" ></a>',
  );

  $platforms['slideshare'] = array(
    'label' => t('SlideShare'),
    'group' => t('Social media: SlideShare'),
  );
  $platforms['slideshare']['templates'] = array(
    'profile-url' => "[?profile_url=[socialmedia:sm-slideshare_url]?]",
    'profile-text-link' => '<a href="[?profile_url=[socialmedia:sm-slideshare_url]?]" title="Visit [?profile_username=[socialmedia:sm-slideshare_username]?] on SlideShare">[?profile_username=[socialmedia:sm-slideshare_username]?]</a>',  
    'profile-button' => '<a href="[?profile_url=[socialmedia:sm-slideshare_url]?]" title="Visit [?profile_username=[socialmedia:sm-slideshare_username]?] on SlideShare"><img src="[?icon-path=[socialmedia:sm-slideshare_icon-path]?]" alt="SlideShare icon" ></a>',
  );  

  $platforms['vimeo'] = array(
    'label' => t('Vimeo'),
    'group' => t('Social media: Vimeo'),
  );
  $platforms['vimeo']['templates'] = array(
    'profile-url' => "[?profile_url=[socialmedia:sm-vimeo_url]?]",
    'profile-text-link' => '<a href="[?profile_url=[socialmedia:sm-vimeo_url]?]" title="Visit [?profile_username=[socialmedia:sm-vimeo_username]?] on Vimeo">[?profile_username=[socialmedia:sm-vimeo_username]?]</a>',  
    'profile-button' => '<a href="[?profile_url=[socialmedia:sm-vimeo_url]?]" title="Visit [?profile_username=[socialmedia:sm-vimeo_username]?] on Vimeo"><img src="[?icon-path=[socialmedia:sm-vimeo_icon-path]?]" alt="Vimeo icon" ></a>',
  );

  $platforms['youtube'] = array(
    'label' => t('YouTube'),
    'group' => t('Social media: YouTube'),
  );
  $platforms['youtube']['templates'] = array(
    'profile-url' => "[?profile_url=[socialmedia:sm-youtube_url]?]",
    'profile-text-link' => '<a href="[?profile_url=[socialmedia:sm-youtube_url]?]" title="Visit [?profile_username=[socialmedia:sm-youtube_username]?] on YouTube">[?profile_username=[socialmedia:sm-youtube_username]?]</a>',  
    'profile-button' => '<a href="[?profile_url=[socialmedia:sm-youtube_url]?]" title="Visit [?profile_username=[socialmedia:sm-youtube_username]?] on YouTube"><img src="[?icon-path=[socialmedia:sm-youtube_icon-path]?]" alt="YouTube icon" ></a>',
  );
  

  
  return $platforms;
}

function socialmedia_widgets_share_platforms_form($data) {
//dsm($data);

  //$icon_filename = array() {
    
  //}
  
  $form = array();
  if (arg(5) == 'add') {
    $element = widgets_element_definition_load(arg(6)); 
  }
  else {
    $element = widgets_element_load(arg(6), arg(4));
  }
  $fields = widgets_field_scan($element['template']);
//dsm($element);
//dsm($fields);
  if (is_array($fields)) {
    foreach ($fields AS $key => $default) {
      $form[$key] = array(
        '#type' => 'textfield',
        '#title' => ucfirst(str_replace(array('_', '-'), ' ', $key)),
        '#default_value' => isset($data[$key]) ? $data[$key] : '',
        '#description' => t('Leave blank to use default %default',
          array(
            '%default' => $default,
          )
        ),              
      );
    }
  }
  if (isset($form['icon-path'])) {
    $options = socialmedia_icon_style_options(TRUE, $element['platform']);
    $form['icon-path'] = array(
      '#type' => 'select',
      '#title' => t('Icon style'),
      '#default_value' => (isset($data['icon-path']) && $data['icon-path']) ? $data['icon-path'] : '',
    //'#description' => t('The name is used in URLs for generated images. Use only lowercase alphanumeric characters, underscores (_), and hyphens (-).'),
      '#options' => $options,
    );
  }
//dsm($form);
  return $form;
}

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

function socialmedia_widgets_element_form_alter(&$form, $set, $element) {
  dsm($form);
  dsm($set);
  dsm($element);
  if ($element['name'] == 'socialmedia_facebook-like-box') {
    $options = array(
      'true' => t('Yes'),
      'false' => t('No'),
    );
    $fields = array(
      'show_faces',
      'data_stream',
      'data_header',
    );
    foreach ($fields AS $field) {
      $form[$field]['#type'] = 'radios';
      $form[$field]['#options'] = $options;
      $form[$field]['#description'] = '';
      $form[$field]['#default_value'] = isset($element['data'][$field]) ? $element['data'][$field] : $form[$field]['#template_default_value'];    
    }
  }
}

function socialmedia_widgets_addthis_tweet_form($data) {
  $options = array(
    '' => t('None'),
    ' tw:count="vertical"' => t('Vertical'),
    ' tw:count="horizontal"' => t('Horizontal'),
  );
  $form['count'] = array(
    '#type' => 'select',
    '#title' => t('Count'),
    '#default_value' => (isset($data['count']) && $data['count']) ? $data['count'] : '',
    //'#description' => t('The name is used in URLs for generated images. Use only lowercase alphanumeric characters, underscores (_), and hyphens (-).'),
    '#options' => $options,
  );
  $form['via'] = array(
    '#type' => 'textfield',
    '#title' => t('Via'),
    '#default_value' => (isset($data['via']) && $data['via']) ? $data['via'] : '',
    '#field_prefix' => '@',
    //'#description' => t('The name is used in URLs for generated images. Use only lowercase alphanumeric characters, underscores (_), and hyphens (-).'),
  );
  return $form;
}

function socialmedia_widgets_addthis_facebook_like_form($data) {
	return socialmedia_widgets_addthis_facebook_form($data, 'like');
}

function socialmedia_widgets_addthis_facebook_send_form($data) {
  return socialmedia_widgets_addthis_facebook_form($data, 'send');
}

function socialmedia_widgets_addthis_facebook_form($data, $type) {
  $options = array(
    '' => t('Standard'),
    ' fb:' . $type . ':layout="button_count"' => t('Button count'),
    ' fb:' . $type . ':layout="box_count"' => t('Box count'),
  );
  $form['layout'] = array(
    '#type' => 'select',
    '#title' => t('Layout'),
    '#default_value' => (isset($data['layout']) && $data['layout']) ? $data['layout'] : '',
    //'#description' => t('The name is used in URLs for generated images. Use only lowercase alphanumeric characters, underscores (_), and hyphens (-).'),
    '#options' => $options,
  );
  /*
  $form['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#default_value' => (isset($data['width']) && $data['width']) ? $data['width'] : '',
    //'#description' => t('The name is used in URLs for generated images. Use only lowercase alphanumeric characters, underscores (_), and hyphens (-).'),
  );

  $form['show_faces'] = array(
    '#type' => 'checkbox',
    '#title' => t('Faces'),
    '#return_value' => ' fb:' . $type . ':show_faces="true"',
    '#default_value' => (isset($data['show_faces']) && $data['show_faces']) ? $data['show_faces'] : '',
    //'#description' => t('The name is used in URLs for generated images. Use only lowercase alphanumeric characters, underscores (_), and hyphens (-).'),
  );
  */
  return $form;
}

function socialmedia_widgets_addthis_google_plusone_form($data) {
  $options = array(
    ' g:plusone:size="standard"' => t('Standard'),
    ' g:plusone:size="small"' => t('Small'),
    ' g:plusone:size="medium"' => t('Medium'),
    ' g:plusone:size="tall"' => t('Tall'),
  );
  $form['size'] = array(
    '#type' => 'select',
    '#title' => t('Size'),
    '#default_value' => (isset($data['size']) && $data['size']) ? $data['size'] : '',
    //'#description' => t('The name is used in URLs for generated images. Use only lowercase alphanumeric characters, underscores (_), and hyphens (-).'),
    '#options' => $options,
  );
  return $form;
}

function socialmedia_widgets_addthis_stumbleupon_form($data) {
  $options = array(
    ' su:bdg:style="4"' => t('Small button (no count)'),
    ' su:bdg:style="6"' => t('Large button (no count)'),
    ' su:bdg:style="1"' => t('Small button with horizontal count'),
    ' su:bdg:style="5"' => t('Large button with verticle count'),
  );
  $form['style'] = array(
    '#type' => 'select',
    '#title' => t('Style'),
    '#default_value' => (isset($data['style']) && $data['style']) ? $data['style'] : '',
    //'#description' => t('The name is used in URLs for generated images. Use only lowercase alphanumeric characters, underscores (_), and hyphens (-).'),
    '#options' => $options,
  );
  return $form;
}

function socialmedia_widgets_addthis_addthis_counter_form($data) {
  $options = array(
    '' => t('Large button with verticle count'),
    ' addthis_pill_style' => t('Small button with horizontal count')
  );
  $form['style'] = array(
    '#type' => 'select',
    '#title' => t('Style'),
    '#default_value' => (isset($data['style']) && $data['style']) ? $data['style'] : '',
    //'#description' => t('The name is used in URLs for generated images. Use only lowercase alphanumeric characters, underscores (_), and hyphens (-).'),
    '#options' => $options,
  );
  return $form;
}



function socialmedia_widgets_default_sets() {
  $sets = array();

  $sets['socialmedia_profile-urls'] = array(
    'style' => 'plain-linebreaks',
    'elements' => array(
      array(
        'name' => 'socialmedia_socialmedia-twitter-profile-url',
        'data' => array(),
        'weight' => 1,
      ),
      array(
        'name' => 'socialmedia_socialmedia-facebook-profile-url',
        'data' => array(),
        'weight' => 1,
      ),
      array(
        'name' => 'socialmedia_socialmedia-linkedin-profile-url',
        'data' => array(),
        'weight' => 1,
      ),
      array(
        'name' => 'socialmedia_socialmedia-googleplus-profile-url',
        'data' => array(),
        'weight' => 1,
      ),
      array(
        'name' => 'socialmedia_socialmedia-youtube-profile-url',
        'data' => array(),
        'weight' => 1,
      ),
    ),
  );
  $sets['socialmedia_profile-buttons'] = array(
    'elements' => array(
      array(
        'name' => 'socialmedia_socialmedia-twitter-profile-button',
        'data' => array(),
        'weight' => 1,
      ),
      array(
        'name' => 'socialmedia_socialmedia-facebook-profile-button',
        'data' => array(),
        'weight' => 1,
      ),
      array(
        'name' => 'socialmedia_socialmedia-linkedin-profile-button',
        'data' => array(),
        'weight' => 1,
      ),
      array(
        'name' => 'socialmedia_socialmedia-googleplus-profile-button',
        'data' => array(),
        'weight' => 1,
      ),
      array(
        'name' => 'socialmedia_socialmedia-youtube-profile-button',
        'data' => array(),
        'weight' => 1,
      ),
    ),
  );
  $sets['socialmedia_addthis-share'] = array(
    'elements' => array(
      array(
        'name' => 'socialmedia_addthis-tweet',
        'data' => array('count' => ' tw:count="vertical"'),
        'weight' => 1,
      ),
      array(
        'name' => 'socialmedia_addthis-facebook-like',
        'data' => array('layout' =>  ' fb:like:layout="box_count"'),
        'weight' => 2,
      ),
      array(
        'name' => 'socialmedia_addthis-google-plusone',
        'data' => array('size' => ' g:plusone:size="tall"'),
        'weight' => 3,
      ),
      array(
        'name' => 'socialmedia_addthis-addthis-counter',
        'data' => array(),
        'weight' => 4,
      ),
    ),
  );

  return $sets;
}