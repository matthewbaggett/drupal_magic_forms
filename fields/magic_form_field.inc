<?php
class magic_form_field extends magic_form_item
{
    protected $name = null;
    protected $label = null;
    protected $default_value = null;
    protected $value = null;
    protected $disabled = false;
    protected $validators = array();
    protected $errors = array();
    protected $classes = array();
    protected $is_mandatory = false;

  /**
   * @param null $name Internal Name for this field
   * @param null $label Visible Name for this field
   * @param null $value Default or Initial Value
   *
   * @return magic_form_field
   */
    public static function factory($name = null, $label = null, $value = null)
    {
        $class = get_called_class();
        $instance = new $class($name, $label, $value);
        return $instance;
    }

  /**
   * Constructor
   * @param null $name Field Computer Name
   * @param null $label Field Human Name
   * @param null $value Field default value
   */
    public function __construct($name = null, $label = null, $value = null)
    {
        $this->name = $name;
        $this->label = t($label);
        $this->value = $value;
        if (method_exists($this, "__post_construct")) {
            $this->__post_construct();
        }
    }

  /**
   * Compute this fields HTML.
   *
   * @return string
   */
    public function __toString()
    {
        $view = new StdClass();
        $view->field = $this;
        return $this->render("form.input.phtml", $view, $this->get_scope() instanceof magic_form ? $this->get_scope()->get_templates_directory(): 'templates_bootstrap');
    }

  /**
   * Add a Validator.
   * @param magic_form_validator $validator
   * @return $this
   */
    public function add_validator(magic_form_validator $validator)
    {
        $this->validators[] = $validator;
        return $this;
    }

  /**
   * Add Validators as a group
   * @return $this
   */
    public function add_validators()
    {
        foreach (func_get_args() as $validator) {
            $this->add_validator($validator);
        }
        return $this;
    }

  /**
   * Decide if the value is valid.
   * @var $validator magic_form_validator
   * @return bool Whether or not the value is valid.
   */
    public function validate()
    {
        $is_ajax = false;
        if (!empty($_SERVER['HTTP_X_REQUESTED_WITH']) && strtolower($_SERVER['HTTP_X_REQUESTED_WITH']) == 'xmlhttprequest') {
            $is_ajax = true;
        }
      //echo "Has " . count($this->validators) . " validators ";
        foreach ($this->validators as $validator) {
            $pass_or_fail = $validator->test($this->get_value());
            $message_params = array(
            ':field_name' => $this->get_name(),
            ':validator_name' => get_class($validator)
            );
            if ($pass_or_fail !== true) {
                if (method_exists($validator, 'user_friendly_failure_message')) {
                    $error = $validator->user_friendly_failure_message($message_params);
                } else {
                    $error = t('Field: :field_name test :validator_name failed', $message_params);
                }
                if (!$is_ajax) {
                    drupal_set_message($error, 'error');
                }
                $this->add_error($error);
            }
        }
        if ($this->has_errors()) {
            return false;
        }
        return true;
    }

  /**
   * Lazyness function to make this field mandatory
   * @return $this
   */
    public function make_mandatory()
    {
        $this->set_mandatory(true);
        $this->add_validator(new magic_form_validator_is_not_null());
        return $this;
    }

  /**
   * Set whether or not this field is mandatory or not
   * @param bool $mandatory_state
   * @return $this
   */
    public function set_mandatory($mandatory_state)
    {
        $this->is_mandatory = $mandatory_state;
        return $this;
    }

  /**
   * Get whether or not this field is mandatory or not
   * @return bool
   */
    public function get_mandatory()
    {
        return $this->is_mandatory;
    }

  /**
   * Get the name of this widget
   *
   * @return string
   */
    public function get_name()
    {
        return $this->name;
    }

  /**
   * Set the name for this widget
   *
   * @param $name
   *
   * @return $this
   */
    public function set_name($name)
    {
        $this->name = $name;
        return $this;
    }

  /**
   * Get the label of this widget
   *
   * @return string
   */
    public function get_label()
    {
        return $this->label;
    }

  /**
   * Set the label for this widget
   *
   * @param $label Label for this widget
   *
   * @return magic_form_field
   */
    public function set_label($label)
    {
        $this->label = $label;
        return $this;
    }

  /**
   * Get the default value of this widget
   *
   * @return string
   */
    public function get_default_value()
    {
        return $this->default_value;
    }

  /**
   * Set the default value of this widget
   *
   * @param $default_value
   *
   * @return magic_form_field
   */
    public function set_default_value($default_value)
    {
        $this->default_value = $default_value;
        return $this;
    }

    public function get_value()
    {
        return $this->value;
    }

  /**
   * @param $value
   *
   * @return magic_form_field
   */
    public function set_value($value)
    {
        $this->value = $value;
        return $this;
    }

  /**
   * Disable this field
   *
   * @return $this
   */
    public function disable()
    {
        $this->disabled = true;
        return $this;
    }

  /**
   * Enable this field
   *
   * @return $this
   */
    public function enable()
    {
        $this->disabled = false;
        return $this;
    }

  /**
   * Determine if this field is disabled
   *
   * @return bool
   */
    public function is_disabled()
    {
        return $this->disabled;
    }

  /**
   * Unset all errors on this field
   *
   * @return $this
   */
    public function clear_errors()
    {
        $this->errors = array();
        return $this;
    }

  /**
   * Add an error on this field
   *
   * @param $error
   *
   * @return $this
   */
    public function add_error($error)
    {
        $this->errors[] = $error;
        return $this;
    }

  /**
   * Does this field have any errors?
   *
   * @return bool
   */
    public function has_errors()
    {
        return count($this->errors) > 0 ? true : false;
    }

  /**
   * Get all errors on this field
   *
   * @return array
   */
    public function get_errors()
    {
        return $this->errors;
    }

  /**
   * Add a class to this field
   *
   * @param $class
   *
   * @return $this
   */
    public function add_class($class)
    {
        $this->classes[] = $class;
        return $this;
    }

  /**
   * Get classes on this field
   *
   * @param null $prefix
   *
   * @return string
   */
    public function get_classes($prefix = null)
    {
        if ($this->has_errors()) {
            $this->add_class($prefix . "error");
        }
        if ($this->is_disabled()) {
            $this->add_class($prefix . 'disabled');
        } else {
            $this->add_class($prefix . 'enabled');
        }
        if ($this->get_mandatory()) {
            $this->add_class($prefix . 'mandatory');
        }
        $this->add_class('weight_' . str_replace(".", "_", $this->get_weight()));
        return implode(" ", $this->classes);
    }

    public function set_attributes($attributes)
    {
        $this->attributes = $attributes;
        return $this;
    }
    public function get_attributes()
    {
        $returnattribute = '';
        if (isset($this->attributes)) {
            foreach ($this->attributes as $k => $v) {
                $returnattribute = $returnattribute . ' ' . $k . '="' . $v . '" ';
            }
            return $returnattribute;
        } else {
            return false;
        }
    }
}
