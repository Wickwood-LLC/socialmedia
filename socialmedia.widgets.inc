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
    'socialmedia_twiter-account-text-link' => array(
      'label' => t('Socialmedia Twitter account text link'),
      'help' => t('Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.'),
      'group' => t('Social media: Twitter'),
      'template' => '<a href="[?twitter_url=[socialmedia:sm-twitter_url]?]">[?twitter_username=[socialmedia:sm-twitter_amp-username]?]</a>',
      'form callback' => 'widgets_template_auto_form',
    ),
    'socialmedia_twitter-account-link' => array(
      'label' => t('Socialmedia Twitter account button'),
      'help' => t('Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.'),
      'group' => t('Social media: Twitter'),
      'template' => '<a href="[?twitter_url=[socialmedia:twitter_url]?]"><img src="[socialmedia:twitter_icon]" alt="[?twitter_amp-username=[socialmedia:twitter_amp-username]?]" /></a>',
      'form callback' => 'widgets_template_auto_form',
    ), 
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
      'template' => '<div class="fb-like-box" data-href="[?href=[socialmedia:sm-facebook_url]?]" data-width="292" data-show-faces="true" data-stream="true" data-header="true"></div>',
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
      'label' => t('Addthis Facebook like button'),
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
      'label' => t('Addthis Facebook send button'),
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
      'label' => t('Addthis Google +1 button'),
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
  );
  
  $elements = array_merge($elements, socialmedia_share_platforms_info());
  
  dsm($elements);

  return $elements;
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



function socialmedia_widgets_default_sets() {
  $sets = array();

  $sets['socialmedia_text-signature'] = array(
    'elements' => array(
      array(
        'name' => 'widgets_custom-markup',
        'data' => array('markup' => 'Follow us on:'),
        'weight' => 0,
      ),
      array(
        'name' => 'socialmedia_twiter-account-text-link',
        'data' => array(),
        'weight' => 1,
      ),
    ),
  );

  return $sets;
}

function socialmedia_share_platforms_info() {
	$platforms = socialmedia_share_platforms();
	$elements = array();
	$labelpost = array(
    'profile-link-text' => t('profile text link'),
	  'profile-link' => t('profile link'),    
    'share-link-text' => t('share text link'),
    'share-link' => t('share link'),
	);
	foreach ($platforms AS $platform_name => $platform) {
		foreach ($platform['templates'] AS $template_name => $template) {
			$lin = 
			$elements['socialmedia_' . $platform_name . '-' . $template_name] = array(
	      'label' => t('Socialmedia @platform @type', 
			    array(
			      '@platform' => $platform['label'],
			      '@type' => $labelpost[$template_name],
			    )),
	      //'help' => t('Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.'),
	      'group' => 'TEST:' . $platform['group'],
	      'template' => $template,
	      //'form callback' => 'socialmedia_widgets_share_platforms_form',
	    );
	    // add form callback if fields
	    if($template_name != 'share-link-text') {
	    	$elements['socialmedia_' . $platform_name . '-' . $template_name]['form callback'] = 'socialmedia_widgets_share_platforms_form';
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
	  'profile-link-text' => '<a href="http://twitter.com/[?profile_username=[socialmedia:sm-twitter_username]?]" title="Visit [?profile_username=[socialmedia:sm-twitter_amp-username]?] on Twitter">[?profile_username=[socialmedia:sm-twitter_amp-username]?]</a>',	
	  'profile-link' => '<a href="http://twitter.com/[?profile_username=[socialmedia:sm-twitter_username]?]" title="Visit [?profile_username=[socialmedia:sm-twitter_amp-username]?] on Twitter"><img src="[?icon=[socialmedia:twitter-icon]?]/twitter.png" alt="Twitter icon" ></a>',
	  'share-link-text' => '<a href="http://twitter.com/share?url=[current-page:url]&text=[current-page:title-plain]" title="Tweet this">Tweet</a>',
	  'share-link' => '<a href="http://twitter.com/share?url=[current-page:url]&text=[current-page:title-plain]" title="Tweet this"><img src="[?icon=[socialmedia:twitter-icon]?]/twitter.png" alt="Twitter icon" ></a>',
	);
	
  $platforms['facebook'] = array(
    'label' => t('Facebook'),
    'group' => t('Social media: Facebook'),
  );
  $platforms['facebook']['templates'] = array(
    'profile-link-text' => '<a href="http://[?profile_url=[socialmedia:sm-facebook_url]?]" title="Visit [?profile_username=[socialmedia:sm-twitter_amp-username]?] on Facebook">[?profile_username=[socialmedia:sm-twitter_amp-username]?]</a>',  
    'profile-link' => '<a href="http://twitter.com/[?profile_username=[socialmedia:sm-twitter_username]?]" title="Visit [?profile_username=[socialmedia:sm-twitter_amp-username]?] on Facebook"><img src="[?icon=[socialmedia:facebook-icon]?]/facebook.png" alt="Facebook icon" ></a>',
    'share-link-text' => '<a href="http://twitter.com/share?url=[current-page:url]&text=[current-page:title-plain]" title="Share on Facebook">Share</a>',
    'share-link' => '<a href="http://twitter.com/share?url=[current-page:url]&text=[current-page:title-plain]" title="Share on Facebook"><img src="[?icon=[socialmedia:twitter-icon]?]/facebook.png" alt="Facebook icon" ></a>',
  );
	return $platforms;
}

function socialmedia_widgets_share_platforms_form($data) {
//dsm($data);
  
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
  if (isset($form['icon'])) {
  	$path_pre = base_path() . drupal_get_path('module', 'socialmedia') . '/icons/icondock/';
  	$options = array(
  	  $path_pre  . '16px' => '16x16',
  	  $path_pre  . '24px' => '24x24',
  	  $path_pre  . '32px' => '32x32',
  	);
  	$form['icon'] = array(
      '#type' => 'select',
      '#title' => t('Icon size'),
      '#default_value' => (isset($data['icon']) && $data['icon']) ? $data['icon'] : '',
    //'#description' => t('The name is used in URLs for generated images. Use only lowercase alphanumeric characters, underscores (_), and hyphens (-).'),
      '#options' => $options,
    );
  }
dsm($form);
  return $form;
}

function socialmedia_platform_icon_info() {
	$icons = array(
	 
	);
}