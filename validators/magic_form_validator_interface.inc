<?php
interface magic_form_validator_interface{
  public function run();
  public function test($data);
}