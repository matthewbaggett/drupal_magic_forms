jQuery(document).ready(function(){
  var widgets = jQuery('form.magic_form .form_row.form_date .widget');
  var calendars = jQuery('.calendar', widgets);
  calendars.hide();

  var show_calendar = function(){
    jQuery('.calendar', this).slideDown('fast');
  };
  var hide_calendar = function(){
    jQuery('.calendar', this).slideUp('fast');
  };
  widgets.hover(show_calendar, hide_calendar);

  jQuery('.prev', calendars).bind('click', function(){
    var calendar = jQuery(this).closest('.calendar');
    jQuery('.month-container.selected', calendar).removeClass('selected').prev().addClass('selected');
  });

  jQuery('.next', calendars).bind('click', function(){
    var calendar = jQuery(this).closest('.calendar');
    jQuery('.month-container.selected', calendar).removeClass('selected').next().addClass('selected');
  });

  jQuery('.calendar-day', calendars).bind('click', function(){
    var calendar = jQuery(this).closest('.calendar');
    var widget = calendar.closest('.widget');
    var input = widget.find('input');
    var date = jQuery(this).attr('rel');
    input.val(date);
  });
});