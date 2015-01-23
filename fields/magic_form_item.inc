<?php
class magic_form_item {
  protected $_scope;
  protected $weight = null;

  public function set_scope($scope) {
    $this->_scope = $scope;
    return $this;
  }

  /**
   * @return magic_form;
   */
  public function get_scope() {
    return $this->_scope;
  }

  public function set_weight($weight){
    $this->weight = $weight;
    return $this;
  }

  public function get_weight(){
    return $this->weight;
  }

  public function apply_weight($form_elements){
    if($this instanceof magic_form_group){
      if(count($this->fields) > 0){
        foreach($this->fields as $field){
          /* @var $field magic_form_item */
          $field->apply_weight($this->fields);
        }
      }
    }
    if($this->get_weight() == null){
      // Find heaviest item.
      $heaviest = null;
      if(count($form_elements) > 0){
        foreach($form_elements as $other_field){
          /* @var $other_field magic_form_item */
          $heaviest = $other_field->get_weight() > $heaviest || $heaviest === null ? $other_field->get_weight() : $heaviest;
        }
      }

      $this->set_weight($heaviest + 1);

      $this->is_dirty = true;
    }
    return $this;
  }

  public function __toJsonArray() {
    $array = array();
    $array['type'] = str_replace('magic_form_field_', '', get_called_class());
    foreach (get_object_vars($this) as $variable => $value) {
      if(is_array($value) && $variable == 'validators'){
        foreach($value as &$validator){
          $validator = $validator->__toJsonArray();
        }
      }
      $array[$variable] = $value;
    }

    if(isset($array['fields']) && count($array['fields']) > 0){
      foreach($array['fields'] as $key => &$field){
        $field = $field->__toJsonArray();
      }
    }
    $array['html'] = $this->__toString();
    return $array;
  }

  public function render($template, $view) {
    $scope = $this->get_scope();
    if (!$scope instanceof magic_form) {
      $render_mode = 'edit';
    } else {
      $render_mode = $scope->get_render_mode();
    }
    return magic_forms_template_view($render_mode . "/" . $template, $view, $this->get_scope() instanceof magic_form ? $this->get_scope()->get_templates_directory(): 'templates_bootstrap');
  }
}