<?php

class magic_form_validator{
  public function test($data){
    $class = get_called_class();
    throw new Exception("{$class} needs to implement test()!");
  }
}

