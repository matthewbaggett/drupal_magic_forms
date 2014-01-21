<?php

function magic_form_examples() {
  $form = magic_form::factory('my-form')
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
    ->add_field(magic_form_field_date::factory('time', 'Time Only')->set_support_date(false)->set_support_time(true))
    ->add_field(magic_form_field_submit::factory('submit', 'Submit'));

  $form->submit(function (magic_form $form) {
    drupal_set_message("Submit happened in form {$form->magic_form_id} / {$form->form_id}");
  });

  // Check to see if an earlier, updated build of this form exists.
  magic_form::check_for_updated_form($form);

  // render the form.
  return $form->__toString();
}