<?php

class magic_form_item
{
  public function __toJsonArray(){
    $array = array();
    foreach(get_object_vars($this) as $variable => $value){
      $array[$variable] = $value;
    }
    return $array;
  }
}