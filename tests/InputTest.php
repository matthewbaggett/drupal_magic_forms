<?php
/**
 * Created by PhpStorm.
 * User: jason.smart
 * Date: 13/02/2015
 * Time: 10:31
 */

class InputTest extends PHPUnit_Framework_TestCase {
    /** @var $magic_form magic_form */
    private $magic_form;

    public function setUp(){

        $this->magic_form = new magic_form();
        $this->magic_form->set_templates_directory("templates_bootstrap");
    }

    public function testTextInput(){
        $new_field = magic_form_field_text::factory("test_text_field", "Test text field");
        $this->magic_form->add_field($new_field);




    }
}

