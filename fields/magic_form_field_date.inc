<?php

class magic_form_field_date extends magic_form_field_text {

  protected $_support_date = true;
  protected $_support_time = true;

  /**
   * @param null $name Internal Name for this field
   * @param null $label Visible Name for this field
   * @param null $value Default or Initial Value
   *
   * @return magic_form_field_date
   */
  public static function factory($name = null, $label = null, $value = null) {
    return parent::factory($name, $label, $value);
  }

  /**
   * Sanitise the date given
   * @return string
   */
  public function get_value() {
    return date(
      $this->get_format(),
      strtotime(parent::get_value())
    );
  }

  /**
   * get the format for date() that this object should use.
   * @return string
   */
  private function get_format() {
    $format_sections = array();
    if ($this->get_support_date()) {
      $format_sections[] = 'Y-m-d';
    }
    if ($this->get_support_time()) {
      $format_sections[] = 'H:i:s';
    }
    return implode(" ", $format_sections);
  }

  /**
   * Set weather or not magic_form_field_date should support dates
   *
   * @param $state bool true or false
   *
   * @return magic_form_field_date $this
   */
  public function set_support_date($state) {
    $this->_support_date = $state;
    return $this;
  }

  /**
   * Get weather or not magic_form_field_date should support dates
   *
   * @return bool
   */
  public function get_support_date() {
    return $this->_support_date;
  }

  /**
   * Set weather or not magic_form_field_date should support times
   *
   * @param $state bool true or false
   *
   * @return magic_form_field_date $this
   */
  public function set_support_time($state) {
    $this->_support_time = $state;
    return $this;
  }

  /**
   * Get weather or not magic_form_field_date should support times
   *
   * @return bool
   */
  public function get_support_time() {
    return $this->_support_time;
  }

  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return $this->render("form.date.phtml", $view);
  }

  /* draws a calendar */

  public function draw_calendar($month,$year){

    /* draw table */
    $calendar = '<table cellpadding="0" cellspacing="0" class="calendar">';

    /* table headings */
    $headings = array('Sun','Mon','Tue','Wed','Thur','Fri','Sat');
    $calendar.= '<thead>';
    $calendar.= '<tr class="calendar-row"><td class="calendar-day-head">'.implode('</td><td class="calendar-day-head">',$headings).'</td></tr>';
    $calendar.= '</thead>';

    /* days and weeks vars now ... */
    $running_day = date('w',mktime(0,0,0,$month,1,$year));
    $days_in_month = date('t',mktime(0,0,0,$month,1,$year));
    $days_in_this_week = 1;
    $day_counter = 0;
    $dates_array = array();

    $calendar.= '<tbody>';
    /* row for week one */
    $calendar.= '<tr class="calendar-row">';

    /* print "blank" days until the first of the current week */
    for($x = 0; $x < $running_day; $x++):
      $calendar.= '<td class="calendar-day-np"> </td>';
      $days_in_this_week++;
    endfor;

    /* keep going with days.... */
    for($list_day = 1; $list_day <= $days_in_month; $list_day++):
      $is_today = false;
      if(date("Y-m-d", strtotime("{$year}-{$month}-{$list_day}")) == date("Y-m-d")){
        $is_today = true;
      }
      $calendar.= '<td class="calendar-day '.($is_today?'calendar-day-today':'').'">';
      /* add in the day number */
      $calendar.= '<div class="day-number">'.$list_day.'</div>';
      $calendar.= '</td>';
      if($running_day == 6):
        $calendar.= '</tr>';
        if(($day_counter+1) != $days_in_month):
          $calendar.= '<tr class="calendar-row">';
        endif;
        $running_day = -1;
        $days_in_this_week = 0;
      endif;
      $days_in_this_week++; $running_day++; $day_counter++;
    endfor;

    /* finish the rest of the days in the week */
    if($days_in_this_week < 8):
      for($x = 1; $x <= (8 - $days_in_this_week); $x++):
        $calendar.= '<td class="calendar-day-np"> </td>';
      endfor;
    endif;

    /* final row */
    $calendar.= '</tr>';
    $calendar.= '</tbody>';

    /* end the table */
    $calendar.= '</table>';

    /* all done, return result */
    return $calendar;
  }



}