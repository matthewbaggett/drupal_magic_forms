jQuery(document).ready(function(){
  var widgets = jQuery('form.magic_form .form_row.form_date .widget');
  var calendars = jQuery('.calendar', widgets);
  calendars.hide();

  var show_calendar = function(){
    jQuery('.calendar', this).show();
  };

  var hide_calendar = function(){
    jQuery('.calendar', this).hide();
  };



  var update_input = function(calendar){
    var widget = calendar.closest('.widget');
    var input = widget.find('input');
    var time_select = jQuery('.time-select', calendar);

    var date = '';
    var time = '';

    var date_field = jQuery('.calendar-day.selected', calendar)
    if(date_field.length > 0){
      date = date_field.attr('rel');
    }

    var time_field = jQuery('dd.time', time_select);
    if(time_field.length > 0){
      time = time_field.html() + ":00";
    }

    // Combine strings.
    var output = date + " " + time;

    // Strip whitespace from start & end
    output = jQuery.trim(output);

    // Set input to this value
    input.val(output);
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
    jQuery('.calendar-day.selected', calendar).removeClass('selected');
    jQuery(this).addClass('selected');
    update_input(calendar);
  });

  jQuery('.time-select input.hour, .time-select input.minute').unbind().bind('change', function(){
    var calendar = jQuery(this).closest('.calendar');
    var widget = calendar.closest('.widget');
    var input = widget.find('input');
    var time_select = jQuery('.time-select', calendar);
    var hour = jQuery('input.hour', time_select).val();
    var minute =  jQuery('input.minute', time_select).val().paddingLeft("00");
    hour = hour.paddingLeft("00");
    minute = minute.paddingLeft("00");
    var time_string = hour + ":" + minute;
    jQuery('dd.time', time_select).empty().append(time_string);
    update_input(calendar);
    jQuery('input.hour', time_select).val(hour);
    jQuery('input.minute', time_select).val(minute);
  });
});