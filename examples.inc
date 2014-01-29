<?php

function magic_form_examples() {
  // Create a new form
  $form = magic_form::factory('my-form');

  // Create a name field
  $name = magic_form_field_text::factory('name', 'Name');
  // Set a default
  $name->set_default_value("Joe Blogs");
  // Set av value
  $name->set_value("Mary Sue");

  // Create a Salutation
  $salutation = magic_form_field_select::factory('salutation', 'Salutation');
  // Add some options to it.
  $salutation->add_options(array(
    0 => 'Please Select',
    1 => 'Mr',
    2 => 'Mrs',
    3 => 'Miss',
    4 => 'Dr'
  ));
  // Add a validator. More than 0 prevents someone using "Please Select"
  $salutation->add_validator(new magic_form_validator_is_numeric_more_than(0));

  // Add them to the form
  $form->add_fields($salutation,$name);

  // Add a load of mixed fields and validators
  $form
    ->add_field(
      magic_form_field_text::factory('phone-number', 'Phone Number')
        ->make_mandatory()
        ->set_default_value('07541 059 344')
        ->add_validator(new magic_form_validator_is_valid_phonenumber())
    )->add_field(
      magic_form_field_text::factory('email', 'Email')
        ->make_mandatory()
        ->set_default_value('matthew@fouroneone.us')
        ->add_validator(new magic_form_validator_is_email())
    )->add_field(
      magic_form_field_textarea::factory('ramble', 'Comment', 'Must be > 50 char, < 100 char')
        ->add_validators(
          new magic_form_validator_is_length_less_than(100),
          new magic_form_validator_is_length_more_than(50)
        )
    )->add_fields(
      magic_form_field_text::factory('phone', 'Phone', '0800 000000')
        ->add_validator(new magic_form_validator_is_valid_phonenumber()),
      magic_form_field_text::factory('email', 'Email', 'joe@example.com')
        ->add_validator(new magic_form_validator_is_email())
    )
    ->add_field(magic_form_field_date::factory('date_time', 'Date & Time')->set_support_date(true)->set_support_time(true))
    ->add_field(magic_form_field_date::factory('date', 'Date Only')->set_support_date(true)->set_support_time(false))
    ->add_field(magic_form_field_date::factory('time', 'Time Only')->set_support_date(false)->set_support_time(true));

  // Add a Series of checkboxes for non-mutually-exclusive options.
  $options = new magic_form_field_checkbox_multi('room-options', 'Room Options');
  $options->add_options(array(
    'aircon' => 'Air Conditioning',
    'nosmoke' => 'Non Smoking',
    'seaview' => 'Sea View',
    'annoying' => 'No Annoying Neighbours',
    'disabled' => 'Disabled access',
    'ground' => 'Ground floor',
    'top' => 'Top floor',
  ));
  $form->add_field($options);

  // Add Submit button to form
  $form->add_field(magic_form_field_submit::factory('submit', 'Submit'));

  // This is our submit handler.
  $form->submit(function (magic_form $form) {
    require_once(drupal_get_path("module", "devel") . "/krumo/class.krumo.php");
    krumo($form->get_fields());
    drupal_set_message("Submit happened in form {$form->magic_form_id} / {$form->form_id}");
  });

  // Check to see if an earlier, updated build of this form exists.
  magic_form::check_for_updated_form($form);

  // render the form.
  return $form->__toString();
}