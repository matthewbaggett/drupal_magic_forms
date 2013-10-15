<?php
class magic_form_item
{
  public function __toJsonArray(){
    $array = array();
    $array['type'] = str_replace('magic_form_field_', '', get_called_class());
    foreach(get_object_vars($this) as $variable => $value){
      $array[$variable] = $value;
    }
    return $array;
  }
}