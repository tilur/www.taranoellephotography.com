jQuery(document).ready(function() {
	jQuery('body').height( jQuery(window).height() );

	/*
	if (jQuery('#thumbnails-wrapper')) {
		jQuery('#thumbnails-wrapper').bind({
			mouseenter: function() {
				jQuery('#thumbnails-wrapper').animate({
					opacity: 1.00
				}, 230, 'swing');

			},
			mouseleave: function() {
				jQuery('#thumbnails-wrapper').animate({
					opacity: 0.20
				}, 230, 'swing');
			}
		});
	}
	*/
});

function tnpLoadBG(type, image, style) {
  if (type == 'gallery') {
    // Need to do an image pre-load here so user doesn't have a bad experience.
		jQuery('#preloader').show();
		objImage = new Image();
		objImage.src = '/sites/www.taranoellephotography.com/files/'+image;
		objImage.onload = function() {
			jQuery('#preloader').hide();
	    output = 'background-image:url(/sites/www.taranoellephotography.com/files/'+image+');';

			if (style != '') {
				output += ' background-position:'+style;
			}

	    jQuery('#page-background').attr('style', output);
		}
  }
}

function tnpGalleryBG() {
}

function tnpScrollThumbnails(direction) {
	offset = jQuery('#thumbnails-inner').offset();
	height = jQuery('#thumbnails-inner').height();

//alert(offset.top + " : " + height + " : " + (offset.top+height));

	if (direction == '+' && offset.top == 95) { return; }
	if (direction == '-' && (height+offset.top < 450)) { return; }

	jQuery('#thumbnails-inner').animate({
		top: direction+"=200"
	}, 230, 'swing');
}

function tnpFade(type, direction) {
	if (direction == 'out') { value = 0.25; }
	else if (direction == 'in') { value = 1.00; }

	switch (type) {
		case 'thumbnails':
			jQuery('#thumbnails-wrapper').animate({
				opacity: value
			}, 230, 'swing');
			break;
	}
}
