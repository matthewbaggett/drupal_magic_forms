<?php

class magic_form_field_multi extends magic_form_field
{
    protected $options;
    protected $labels = 'after';


  /**
   * Add an option to the options array
   *
   * @param string $value  The label of the option selected
   * @param null   $key The value of the option selected - Unique.
   * @return $this
   */
    public function add_option($value, $key = null)
    {
        if ($key) {
            $this->options[$key] = $value;
        } else {
            $this->options[] = $value;
        }
        return $this;
    }

  /**
   * Get assigned options
   *
   * @return array of options
   */
    public function get_options()
    {
        return $this->options;
    }

  /**
   * Set assigned options
   * @param array $options options
   * @return $this
   */
    public function set_options($options)
    {
        $this->options = $options;
        return $this;
    }

  /**
   * Pass an array of options to the magic form field in the format key => value
   *
   * @param $array_of_options
   *
   * @return magic_form_field_switch
   */
    public function add_options($array_of_options)
    {
        foreach ($array_of_options as $key => $value) {
            if (class_exists('active_record') || class_exists('data_object')) {
                if ($value instanceof active_record || $value instanceof data_object) {
                    $this->add_option($value->get_label(), $value->get_id());
                    continue;
                }
            }
            $this->add_option($value, $key);
        }
        return $this;
    }

  /**
   * Remove an option by key
   *
   * @param $key_of_option
   *
   * @return magic_form_field_multi
   */
    public function remove_option($key_of_option)
    {
        unset($this->options[$key_of_option]);
        return $this;
    }

  /**
   * Remove an array of options by key
   *
   * @param $array_of_keys
   *
   * @return magic_form_field_multi
   */
    public function remove_options($array_of_keys)
    {
        foreach ($array_of_keys as $key) {
            $this->remove_option($key);
        }
        return $this;
    }

    public function sort_options()
    {
        $options = array();
        foreach ($this->get_options() as $key => $value) {
            $options[$value] = ['key' => $key, 'value' => $value];
        }
        ksort($options);
        $sorted_options = array();
        foreach ($options as $option) {
            $sorted_options[$option['key']] = $option['value'];
        }
        $this->set_options($sorted_options);
    }

  /**
   * Set labels to go before input
   *
   * @return $this
   */
    public function set_labels_before()
    {
        $this->labels = 'before';
        return $this;
    }

  /**
   * Set labels to go after input
   *
   * @return $this
   */
    public function set_labels_after()
    {
        $this->labels = 'after';
        return $this;
    }

  /**
   * Is the label going after?
   *
   * @return bool
   */
    public function is_label_after()
    {
        if ($this->labels == 'after') {
            return true;
        }
        return false;
    }
}
