<?php
/**
 * Created by PhpStorm.
 * User: jason.smart
 * Date: 13/02/2015
 * Time: 10:31
 */

class FormTest extends PHPUnit_Framework_TestCase
{

    /** @var $magic_form magic_form */
    private $magic_form;

    public function setUp()
    {
        $this->magic_form = new magic_form();
        $this->magic_form->set_templates_directory("templates_bootstrap");

        //Set Some Vars
        $this->input_default_name = 'test_text_field';
        $this->input_default_label = 'Test text field';
    }

    public function testForm()
    {
        $new_field = magic_form_field_text::factory($this->input_default_name, $this->input_default_label);
        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Check Form Class
        $this->assertEquals("magic_bootstrap_form", $form->attr['class']);
        //Check Action is Empty
        $this->assertEmpty($form->attr['action']);

        //Find Form ID
        $magic_form_id_field = $form->find("input[name=magic_form_id]")[0];
        //Find Text Input
        $test_text_field = $form->find("input[name=test_text_field]")[0];

        //Check Form ID
        $this->assertEquals("hidden", $magic_form_id_field->attr['type'], "Check Form Type Hidden");
        $this->assertEquals("magic_form_id", $magic_form_id_field->attr['name'], "Check Name magic_form_id");
        $this->assertStringMatchesFormat("magic_form_%x", $magic_form_id_field->attr['value'], "Check value magic_form_x");


    }

    public function testFormSubmit()
    {

        $new_field = magic_form_field_text::factory($this->input_default_name, $this->input_default_label);
        $this->magic_form->add_field($new_field);

        $this->magic_form->add_field(magic_form_field_submit::factory('submit', 'Submit'));

        // This is our submit handler.
        $this->magic_form->submit(function (magic_form $form) {
            require_once(drupal_get_path("module", "devel") . "/krumo/class.krumo.php");
            krumo($form->get_fields());
            drupal_set_message("Submit happened in form {$form->magic_form_id} / {$form->form_id}");
        });

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Submit Button
        $test_submit_button = $form->find("button[name=submit]")[0];

        //Check Submit Button
        $this->assertEquals("submit", $test_submit_button->attr['id'], "Check ID Submit");
        $this->assertEquals("submit", $test_submit_button->attr['name'], "Check Name Submit");

    }
}
