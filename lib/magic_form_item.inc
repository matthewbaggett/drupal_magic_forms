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
    $scope = $this->get_scope();
    if(!$scope instanceof magic_form){
      $render_mode = 'edit';
    }else{
      $render_mode = $scope->get_render_mode();
    }
    return magic_forms_template_view($render_mode . "/" . $template, $view);
  }
}