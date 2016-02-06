<?php

class magic_form_validator_is_email extends magic_form_validator implements magic_form_validator_interface
{
    public function test($email)
    {
        if (filter_var($email, FILTER_VALIDATE_EMAIL)) {
            return true;
        } else {
            return false;
        }
    }

    public function user_friendly_failure_message($message_params)
    {
        return t("Not a valid email address");
    }
}
