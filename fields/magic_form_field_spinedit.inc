<?php

class magic_form_field_spinedit extends magic_form_field
{
    private $min;
    private $max;
    private $step;
    private $options;
    private $option;
  /*private $show_tooltip;
  private $show_increments;
  private $show_min;
  private $show_max;*/

  /**
   * @param null $name Internal Name for this field
   * @param null $label Visible Name for this field
   * @param null $value Default or Initial Value
   *
   * @return magic_form_field_spinedit
   */
    public static function factory($name = null, $label = null, $value = null)
    {
        return parent::factory($name, $label, $value);
    }

    public function __post_construct()
    {

    }

    public function set_min($min)
    {
        $this->min = $min;
        return $this;
    }

    public function get_min()
    {
        return $this->min;
    }

    public function set_max($max)
    {
        $this->max = $max;
        return $this;
    }

    public function get_max()
    {
        return $this->max;
    }


    public function set_step($step)
    {
        $this->step = $step;
        return $this;
    }

    public function get_step()
    {
        return $this->step;
    }


    public function __toString()
    {
        $view = new StdClass();
        $view->field = $this;
        return $this->render("form.spinedit.phtml", $view, $this->get_scope() instanceof magic_form ? $this->get_scope()->get_templates_directory(): 'templates_bootstrap');
    }
}
