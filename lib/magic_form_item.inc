<?php
class magic_form_item
{
  protected $_scope;

  public function set_scope($scope){
    $this->_scope = $scope;
    return $this;
  }

  /**
   * @return magic_form;
   */
  public function get_scope(){
    return $this->_scope;
  }

  public function __toJsonArray(){
    $array = array();
    $array['type'] = str_replace('magic_form_field_', '', get_called_class());
    foreach(get_object_vars($this) as $variable => $value){
      $array[$variable] = $value;
    }
    return $array;
  }

  public function render($template, $view){
    return magic_forms_template_view($this->get_scope()->get_render_mode() . "/" . $template, $view);
  }
}