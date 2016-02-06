<?php

/**
 * Class magic_form
 * @var $magic_form_id INTEGER
 * @var $form_id VARCHAR(24)
 * @var $created DATETIME
 * @var $uid INTEGER
 * @var $form_elements TEXT
 * @var $submit_function TEXT
 * @var $submit_destination TEXT
 * @var $render_mode VARCHAR(4)
 * @var $action VARCHAR(255)
 * @var $classes TEXT
 * @var $form_name VARCHAR(255)
 * @var $fields_to_omit TEXT
 * @var $autocomplete TEXT
 */
class magic_form extends \Thru\ActiveRecord\ActiveRecord
{
    protected $_table = "magic_forms";

    const MAGIC_FORM_RENDER_MODE_VIEW = 'view';
    const MAGIC_FORM_RENDER_MODE_EDIT = 'edit';

  // TODO: make these protected.
    public $magic_form_id;
    public $form_id = null;
    public $created;
    public $uid;
    public $form_elements;
    public $submit_function;
    public $submit_destination = null;
    private $templates_directory = 'templates_bootstrap';
    public $render_mode = self::MAGIC_FORM_RENDER_MODE_EDIT;
    public $action = null;
    public $classes = array();
    public $form_name = null;
    public $fields_to_omit = array();
    public $autocomplete = false;

    private $is_dirty = false;

    const inactivity_max_time = '24 hours';

  /**
   * Constructor
   * @param null $form_name Form name
   */
    public function __construct($form_name = null)
    {
        if ($this->form_id === null) {
            $this->form_id = uniqid('magic_form_');
        }
        if ($form_name !== null) {
            $this->set_form_name($form_name);
        }
        $this->created = date("Y-m-d H:i:s");
        $this->uid = user_active_record::current()->uid;
    }

  /**
   * Factory method
   * @param null $form_name Form name
   * @return magic_form
   */
    public static function factory($form_name = null)
    {
        return new magic_form($form_name);
    }

    public function __destruct()
    {
      //if($this->is_dirty == true){
      //  $this->__save(false);
      //}
    }

    public function __save($automatic_reload = true)
    {
        return $this->save($automatic_reload);
    }

    public function is_update()
    {
      // Check for collisions, return true if there is one.
        if (magic_form::search()->where('magic_form_id', $this->magic_form_id)->where('form_id', $this->form_id)->count() > 0) {
            return true;
        }
        return parent::is_update();
    }

    public function __pre_save()
    {
        $this->__magic_form_serialise();
    }

    public function __post_save()
    {
        $this->__magic_form_deserialise();
    }

    public function __post_construct()
    {
        $this->__magic_form_deserialise();
    }

    private function __magic_form_serialise()
    {
        if (is_array($this->form_elements) || is_object($this->form_elements)) {
            $this->form_elements = $this->__encode($this->form_elements);
        }
        if (is_array($this->submit_function) || is_object($this->submit_function)) {
            $this->submit_function = $this->__encode($this->submit_function);
        }
        if (is_array($this->submit_destination) || is_object($this->submit_destination)) {
            $this->submit_destination = $this->__encode($this->submit_destination);
        }
        if (is_array($this->classes) || is_object($this->classes)) {
            $this->classes = $this->__encode($this->classes);
        }
        if (is_array($this->fields_to_omit) || is_object($this->fields_to_omit)) {
            $this->fields_to_omit = $this->__encode($this->fields_to_omit);
        }
        if (is_array($this->autocomplete) || is_object($this->autocomplete)) {
            $this->autocomplete = $this->__encode($this->autocomplete);
        }
    }

    private function __magic_form_deserialise()
    {
        if (is_string($this->form_elements)) {
            $this->form_elements = $this->__decode($this->form_elements);
        }
        if (is_string($this->submit_function)) {
            $this->submit_function = $this->__decode($this->submit_function);
        }
        if (is_string($this->submit_destination)) {
            $this->submit_destination = $this->__decode($this->submit_destination);
        }
        if (is_string($this->classes)) {
            $this->classes = $this->__decode($this->classes);
        }
        if (is_string($this->fields_to_omit)) {
            $this->fields_to_omit = $this->__decode($this->fields_to_omit);
        }
        if (is_string($this->autocomplete)) {
            $this->autocomplete = $this->__decode($this->autocomplete);
        }
    }

    public function __encode($thing)
    {
        $serialised = serialize($thing);
        $encoded = base64_encode($serialised);
        return $encoded;
    }

    public function __decode($encoded)
    {
        $serialized = base64_decode($encoded);
        $thing = unserialize($serialized);
        return $thing;
    }

    public function set_form_name($name)
    {
        $name = str_replace(" ", "-", $name);
        $name = str_replace("_", "-", $name);
        $this->form_name = $name;
        return $this;
    }

    public function get_form_name()
    {
        return $this->form_name;
    }

    public function set_autocomplete_enable()
    {
        return $this->set_autocomplete(true);
    }

    public function set_autocomplete_disable()
    {
        return $this->set_autocomplete(false);
    }

    public function set_autocomplete($mode)
    {
        $this->autocomplete = $mode;
        return $this;
    }

    public function get_autocomplete()
    {
        return $this->autocomplete;
    }

    public function set_render_mode($render_mode)
    {
        $this->render_mode = $render_mode;
        return $this;
    }

    public function get_render_mode()
    {
        return $this->render_mode;
    }

    public static function cleanup_expired_forms()
    {
      // Expire old magic forms
        $expired_forms = magic_form::search()->where('created', date('Y-m-d H:i:s', strtotime(self::inactivity_max_time . ' ago')), '<=')->exec();
        foreach ($expired_forms as $expired_form) {
          /* @var $expired_form magic_form */
            $expired_form->delete();
        }
    }

    public function has_field($field_name)
    {
        if (isset($this->form_elements[$field_name])) {
            return true;
        }
        return false;
    }

    public function add_field(magic_form_item $field)
    {
        $field->apply_weight($this->form_elements);
        $this->form_elements[$field->get_name()] = $field;
        return $this;
    }

    public function add_fields()
    {
        foreach (func_get_args() as $argument) {
            $argument->set_scope($this);
            $this->add_field($argument);
        }
        return $this;
    }

    public function remove_field($field_name)
    {

        foreach ($this->form_elements as $k => $form_element) {
            if ($form_element instanceof magic_form_field) {
                if ($form_element->get_name() == $field_name) {
                    unset($this->form_elements[$k]);
                }
            }
            if ($form_element instanceof magic_form_group) {
                $form_element->remove_field($field_name);
            }
        }
        return $this;
    }

    public function remove_fields()
    {
        foreach (func_get_args() as $argument) {
            $this->remove_field($argument);
        }
        return $this;
    }

    public function omit_field($name)
    {
        $this->fields_to_omit[] = $name;
        return $this;
    }

    public function omit_fields()
    {
        foreach (func_get_args() as $name) {
            $this->omit_field($name);
        }
        return $this;
    }

    public function replace_field($name, magic_form_field $field)
    {
        if (!isset($this->form_elements[$name])) {
            drupal_set_message("Cannot replace field {$name}, does not exist in form.", "warning");
        }
        $this->form_elements[$name] = $field;
        return $this;
    }

    public function relabel($array_of_labels_to_relabel)
    {
        foreach ($array_of_labels_to_relabel as $original => $replacement) {
            foreach ($this->form_elements as &$form_element) {
              /* @var $form_element magic_form_field */
                if (method_exists($form_element, 'get_label') && method_exists($form_element, 'set_label')) {
                    if ($form_element->get_name() == $original) {
                        $form_element->set_label($replacement);
                    }
                }
            }
        }
        return true;
    }

  /**
   * Get a named field.
   *
   * @param $name
   *
   * @return magic_form_field|magic_form_group
   */
    public function get_field($name)
    {
      //echo "Searching form for {$name}<br />";
      //krumo($this->form_elements);
        foreach ($this->form_elements as $element) {
            if ($element->get_name() == $name) {
                return $element;
            }
            if (get_class($element) == 'magic_form_group') {
                $sub_fields = $element->get_fields();
                if (count($sub_fields) > 0) {
                  //echo "Introspecting children\n";
                    foreach ($sub_fields as $k => $sub_element) {
                      //echo "Is it { $sub_element->get_name()} == {$name}?<br />";
                        if ($sub_element->get_name() == $name) {
                            return $sub_element;
                        }
                    }
                }
            }
        }
        watchdog("magic-form", "Cannot find field: :name", array(':name' => $name), WATCHDOG_WARNING);
        return false;
    }

    public function seek_field($name)
    {
        foreach ($this->form_elements as $element) {
            if ($element->get_name() == $name) {
                return $element;
            }
            if ($element instanceof magic_form_group) {
                $found = $element->seek_field($name);
                if ($found instanceof magic_form_item) {
                    return $found;
                }
            }
        }
        return false;
    }

    public function get_fields()
    {

        $all_elements = array();
        $all_elements = array_merge($all_elements, $this->form_elements);
        $output_elements = array();

        $output_elements = array_merge($output_elements, $all_elements);

        foreach ($all_elements as &$element) {
            if ($element instanceof magic_form_group) {
                $element_sub_fields = $element->get_fields();
                if (count($element_sub_fields) > 0) {
                    foreach ($element_sub_fields as $field) {
                        $output_elements[] = $field;
                    }
                }
            }
        }

        return $output_elements;
    }

    private function _weight_sort(magic_form_item $a, magic_form_item $b)
    {
        return $a->get_weight() == $b->get_weight() ? 0 : ( $a->get_weight() > $b->get_weight() ) ? 1 : -1;
    }

    public function __toString()
    {
        try {
            $this->__save(false);
          // Create the view.
            $view = new StdClass();
            $view->form_rows = $this->form_elements;

            usort($view->form_rows, array($this, '_weight_sort'));

          // Check we have a callback or an action
            if (!(is_callable($this->submit_function) || $this->action !== null)) {
                drupal_set_message("DANGER WILL ROBINSON! No submit handler has been written for this form nor has an action has been set!", 'error');
            }
            if (!count($view->form_rows) > 0) {
                drupal_set_message("DANGER WILL ROBINSON! No form elements in this form!", 'error');
            }

            if (count($view->form_rows) > 0) {
              // Iterate over rows
                foreach ($view->form_rows as $key => &$row) {
                  /* @var $row magic_form_item */
                    $row->set_scope($this);
                    if (in_array($row->get_name(), $this->fields_to_omit)) {
                        unset($view->form_rows[$key]);
                    }
                }
                $view->action = $this->get_action();
                $view->form_name = $this->get_form_name();
                $view->form_id = $this->get_form_id();
                $view->classes = $this->get_classes();
                $view->autocomplete = $this->autocomplete;
                $view->scope = $this;
                $this->__save();
                return magic_forms_template_view($this->get_render_mode() . "/" . "form.phtml", $view, $this->get_templates_directory());
            }
            return false;
        } catch (Exception $e) {
            return "Exception: {$e->getMessage()}";
        }
    }

    public function get_action()
    {
        if ($this->action) {
            return $this->action;
        } else {
            return $_SERVER['REQUEST_URI'];
        }
    }

    public function set_action($target)
    {
        $this->action = $target;
        return $this;
    }

  /**
   * This is how you set the callback on submit.
   * @param $submit_function
   * @return $this
   */
    public function submit($submit_function)
    {
        $this->submit_function = new magic_serialisable_closure($submit_function);
        $this->save();
        return $this;
    }

    public function set_submit_destination($submit_destination)
    {
        $this->submit_destination = $submit_destination;
        return $this;
    }

    public function get_submit_destination()
    {
        return $this->submit_destination;
    }

    public function do_submit()
    {
        $this->populate_with_request();
        if (!is_callable($this->submit_function)) {
            throw new exception("No submit handler has been written for this form!");
        }
        foreach ($this->get_fields() as $field) {
          // Only clear errors & re-validate magic_form_fields, magic_form_group has no validators or errors to speak of.
            if ($field instanceof magic_form_field) {
              /* @var $field magic_form_field */
                $field->clear_errors();
              //echo "Validating {$field->get_name()} ";
                $field->validate();
              //echo "- has " . count($field->get_errors()) . " errors \n";
            }
        }
        $this->save();
        $this->submit_function->__invoke($this);
    }

    private function populate_with_request()
    {
        foreach ($_POST as $key => $value) {
            switch ($key) {
                case 'magic_form_id':
                  // Do nothing;
                    break;

                case 'q':
                  // Lol, drupal.
                    break;

                case strpos("ignore", $key) !== false:
                  // ignore fields prefixed with 'ignore'
                    break;

                default:
                    $item = $this->seek_field($key);

                    if (!$item instanceof magic_form_field) {
                        $item = new magic_form_field();
                        $item->set_name($key);
                        $item->set_label($key);
                    }
                    $item->set_value($value);
                    $this->form_elements[$key] = $item;
            }
        }
        $this->save();
    }

    public function get_form_id()
    {
        return $this->form_id;
    }

    public static function process($magic_form_id)
    {
        $magic_form = magic_form::search()->where('form_id', $magic_form_id)->execOne();
        if ($magic_form instanceof magic_form) {
            $magic_form->do_submit();
        } else {
            drupal_set_message("Uhoh... The form expired after " . self::inactivity_max_time . "! Please try again.", "error");
            header("Location: {$_SERVER['HTTP_REFERER']}");
            exit;
        }
    }

    public function add_error($message, $element = null)
    {
        drupal_set_message($message, 'error');

        $field = $this->get_field($element);
        if ($field instanceof magic_form_field) {
            $field->add_error($message);
        }
    }

  /**
   * Decide if this form has any errors.
   * @return bool
   */
    public function has_errors()
    {
        foreach ($this->form_elements as $field) {
          /* @var $field magic_form_field */
            if ($field instanceof magic_form_field) {
                if ($field->has_errors()) {
                    return true;
                }
            }
        }
        return false;
    }

    public function get_errors()
    {
        $errors = array();
        foreach ($this->form_elements as $field) {
          /* @var $field magic_form_field */
            if ($field instanceof magic_form_field) {
                if ($field->has_errors()) {
                    $errors[] = $field->get_name() . ": " . implode(", ", $field->get_errors());
                }
            }
        }
        return $errors;
    }

    public function add_default($value, $element = null)
    {
        $field = $this->get_field($element);
        if ($field instanceof magic_form_field) {
            $field->set_value($value);
        }
        return $this;
    }

    public function set_defaults($defaults)
    {
        foreach ($defaults as $element_name => $value) {
            $this->add_default($value, $element_name);
        }
        return $this;
    }

    public function set_templates_directory($templates_directory)
    {
        $this->templates_directory = $templates_directory;
        return $this;
    }

    public function get_templates_directory()
    {
        return $this->templates_directory;
    }

    public function add_class($class)
    {
        $this->classes[] = $class;
        return $this;
    }

    public function get_classes()
    {
        $classes = array();
        if ($this->get_form_name()) {
            $classes[] = magic_forms_mangle_to_css_class($this->get_form_name());
        }
        $classes = array_merge($classes, $this->classes);
        return $classes;
    }

    public function check_for_existing_form()
    {
        if (isset($_REQUEST['magic_form_id'])) {
            $query = self::search();
            if ($this->form_name) {
                $query->where('form_name', $this->form_name);
            }
            $query
            ->where('uid', user_active_record::current()->uid)
            ->where('created', date("Y-m-d H:i:s", strtotime('1 hour ago')), '>=')
            ->where('form_id', $_REQUEST['magic_form_id']);
            $match = $query->execOne();
            if ($match instanceof magic_form) {
                return $match;
            }
        }
        return false;
    }

    public static function check_for_updated_form(magic_form &$form)
    {
        $match = $form->check_for_existing_form();
        if ($match) {
            $form = $match;
        }
        return $form;
    }

    public function __toJson($anticipated_rows = NULL)
    {
        $response = new StdClass();
        foreach ($this as $name => $field) {
            $response->$name = $field;
        }
        foreach ($this->form_elements as $i => $field) {
          /* @var $field magic_form_field */
            $field->apply_weight($this->form_elements);
        }
        foreach ($this->form_elements as $i => $field) {
          /* @var $field magic_form_field */
            $response->fields[$i] = $field->__toJsonArray();
        }
        unset($response->form_elements);

        header("Content-type: application/json");
        echo magic_form_print_json(json_encode($response));
        exit;
    }
}
