<?php

class magic_form_validator_is_valid_phonenumber extends magic_form_validator implements magic_form_validator_interface
{
    public function test($data)
    {
        $pattern = "/^(\\+44\\s?7\\d{3}|\\(?07\\d{3}\\)?)\\s?\\d{3}\\s?\\d{3}$/";

        $match = preg_match($pattern, $data);

        if ($match != false) {
          // We have a valid phone number
            return true;
        } else {
          // We have an invalid phone number
            return false;
        }
    }

    public function user_friendly_failure_message($message_params)
    {
        return t("Not a valid phone number");
    }
}
