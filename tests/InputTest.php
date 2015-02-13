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

        $html = $this->magic_form->__toString();


        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        $this->assertEquals("magic_bootstrap_form", $form->attr['class']);

        $this->assertEmpty($form->attr['action']);

        $magic_form_id_field = $form->find("input[name=magic_form_id]")[0];

        $test_text_field = $form->find("input[name=test_text_field]")[0];

        $this->assertEquals("hidden", $magic_form_id_field->attr['type']);
        $this->assertEquals("magic_form_id", $magic_form_id_field->attr['name']);
        $this->assertStringMatchesFormat("magic_form_%x", $magic_form_id_field->attr['value']);




    }
}

