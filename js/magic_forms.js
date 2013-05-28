jQuery(document).ready(function () {
  var form = jQuery('form.magic_form');
  jQuery('select, input, textarea', form).bind('change', function () {
    jQuery(this).addClass('changed');
  });
});