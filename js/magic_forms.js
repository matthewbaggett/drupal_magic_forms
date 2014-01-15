jQuery(document).ready(function () {
  var form = jQuery('form.magic_form');
  jQuery('select, input, textarea', form).bind('change', function () {
    jQuery(this).addClass('changed');
  });
});

function magic_form_field(type, name, label, value, default_value) {
  if (typeof(value) == 'undefined') {
    value = '';
  }
  this.type = type;
  this.name = name;
  this.label = label;
  this.value = value;
  this.default_value = default_value;
  this.options = [];
  this.disabled = false;
  this.events = [];


  this._get_mass_selector = function () {
    return '' +
      '.form_row.field-' + this.name + ' input,' +
      '.form_row.field-' + this.name + ' textarea,' +
      '.form_row.field-' + this.name + ' select,' +
      '.form_row.field-' + this.name + '.form_radio .radio_group input[type=radio]'
  };

  this._get_input_field = function () {
    var selector = this._get_mass_selector();
    return jQuery(selector);
  };

  this.set_value = function (value) {
    if (typeof(value) !== 'undefined' && value !== null) {
      value = value.toString();
    }
    this.value = value;

    // Set the value
    this._get_input_field().val(value);
    this._get_input_field().attr('placeholder', this.default_value);

    // If its an option, we got a little more heavy liftin' to do.
    var select = jQuery('.form_row.field-' + this.name + ' select');
    if (select.length > 0) {
      jQuery("option", select).removeAttr('selected');
      jQuery("option[value='" + value + "']", select).attr('selected', 'selected');
    }

    // Trigger changed state.
    this._get_input_field().trigger('change');
    return this;
  };

  this.get_value = function () {
    var val;
    val = jQuery('.form_row.field-' + this.name + ' input').val();
    if (typeof(val) == 'undefined') {
      val = jQuery('.form_row.field-' + this.name + ' textarea').val();
    }
    if (typeof(val) == 'undefined') {
      val = jQuery('.form_row.field-' + this.name + ' select option:selected').val();
    }
    return val;
  }

  this.get_value_text = function () {
    var val;
    val = jQuery('.form_row.field-' + this.name + ' input').val();
    if (typeof(val) == 'undefined') {
      val = jQuery('.form_row.field-' + this.name + ' textarea').val();
    }
    if (typeof(val) == 'undefined') {
      val = jQuery('.form_row.field-' + this.name + ' select option:selected').val();
    }
    return val;
  }

  this.add_option = function (option_key, option_value) {
    this.options.push({
      key: option_key,
      value: option_value
    });
    jQuery('.form_row.field-' + this.name + ' select')
      .append("<option value=\"" + option_key + "\">" + option_value + "</option>")
    var option_id = this.name + '_' + option_key;
    jQuery('.form_row.field-' + this.name + ' .radio_group')
      .append("<div class=\"radio_group_option\"><input name=\"" + this.name + "\" id=\"" + option_id + "\" type=\"radio\" value=\"" + option_key + "\"><label for=\"" + option_id + "\">" + option_value + "</label></div>");
    return this;
  };

  this.remove_option = function (option_key) {
    var options = this.options;
    jQuery(options).each(function (i, item) {
      if (item.key == option_key) {
        options.splice(i, 1);
      }
    });

    jQuery('.form_row.field-' + this.name + ' select option[value=' + option_key + ']').remove();
    jQuery('.form_row.field-' + this.name + ' .radio_group radio_group_option input[value=' + option_key + ']').parent().remove();
  }

  this.empty = function () {
    this.options = [];
    jQuery('.form_row.field-' + this.name + ' select option').remove();
    jQuery('.form_row.field-' + this.name + ' .radio_group .radio_group_option').remove();
    return this;
  };

  this.on_change = function (callback) {
    this.
      _get_input_field()
      .unbind('change')
      .bind('change', callback);
    return this;
  };

  this.disable = function () {
    this.disabled = true;
    this._get_input_field()
      .attr('readonly', 'readonly')
      .addClass('disabled')
      .removeClass('enabled');
    return this;
  }

  this.enable = function () {
    this.disabled = false;
    this._get_input_field()
      .removeAttr('readonly')
      .addClass('enabled')
      .removeClass('disabled');
    return this;
  }

  this.html = function () {
    //console.log(this, this.name);
    if (this.type == 'input' || this.type == 'text') {
      return '' +
        '<div class="form_row form_input field-' + this.name + '">' +
        '  <label for="' + this.name + '">' + this.label + '</label>' +
        '  <div class="widget">' +
        '    <input type="text" placeholder="' + this.placeholder + '" class="' + (this.disabled ? 'disabled' : 'enabled') + '" value="' + this.value + '" name="' + this.name + '" id="' + this.name + '" ' + (this.disabled ? 'readonly' : '') + '>' +
        '  </div>' +
        '  <div class="clear"></div>' +
        '</div>';
    } else if (this.type == 'checkbox') {
      var is_checked = '';
      if (this.value == 1) {
        is_checked = 'checked="checked"';
      }
      return '' +
        '<div class="form_row form_checkbox field-' + this.name + '">' +
        '  <div class="widget">' +
        '    <input type="checkbox" placeholder="' + this.placeholder + '" class="' + (this.disabled ? 'disabled' : 'enabled') + '" ' + is_checked + '" name="' + this.name + '" id="' + this.name + '" ' + (this.disabled ? 'readonly' : '') + '>' +
        '    <label for="' + this.name + '">' + this.label + '</label>' +
        '  </div>' +
        '  <div class="clear"></div>' +
        '</div>';
    } else if (this.type == 'textarea') {
      return '' +
        '<div class="form_row form_textarea field-' + this.name + '">' +
        '  <label for="' + this.name + '">' + this.label + '</label>' +
        '  <div class="widget">' +
        '    <textarea type="text" class="' + (this.disabled ? 'disabled' : 'enabled') + '" name="' + this.name + '" id="' + this.name + '" ' + (this.disabled ? 'readonly' : '') + '>' + this.value + '</textarea>' +
        '  </div>' +
        '  <div class="clear"></div>' +
        '</div>';
    } else if (this.type == 'select') {
      return '' +
        '<div class="form_row form_select field-' + this.name + '">' +
        '  <label for="' + this.name + '">' + this.label + '</label>' +
        '  <div class="widget">' +
        '    <select class="' + (this.disabled ? 'disabled' : 'enabled') + '" name="' + this.name + '" id="' + this.name + '" ' + (this.disabled ? 'readonly' : '') + '>' + this.html_select_options() + '</select>' +
        '  </div>' +
        '  <div class="clear"></div>' +
        '</div>';
    } else if (this.type == 'radio') {
      return '' +
        '<div class="form_row form_radio field-' + this.name + '">' +
        '  <div class="radio_group">' +
        this.html_radio_options() +
        '    <div class="clear"></div>' +
        '  </div>' +
        '</div>';
    } else if (this.type == 'submit') {
      return '' +
        '<div class="form_row form_submit field-' + this.name + '">' +
        '  <div class="widget">' +
        '    <input type="submit" class="' + (this.disabled ? 'disabled' : 'enabled') + '" name="' + this.name + '" id="' + this.name + '" value="' + this.label + '"/ ' + (this.disabled ? 'readonly' : '') + '>' +
        '  </div>' +
        '  <div class="clear"></div>' +
        '</div>';
    } else if (this.type == 'hidden') {
      return '' +
        '<div class="form_row form_hidden field-' + this.name + '">' +
        '    <input type="hidden" value="' + this.value + '" name="' + this.name + '" id="' + this.name + '">' +
        '</div>';
    } else {
      return 'Unsupported type: ' + this.type;
    }
  };

  this.html_select_options = function () {
    var option;
    var option_html = '';
    while (option = this.options.shift()) {
      option_html += "<option value=\"" + option.key + "\">" + option.value + "</option>";
    }
    return option_html;
  };

  this.html_radio_options = function () {
    var radio;
    var radio_html = '';
    while (radio = this.options.shift()) {
      var name = this.name + "_" + radio.key;
      radio_html += "<div class=\"radio_group_option\">";
      radio_html += "  <input name=\"" + this.name + "\" id=\"" + name + "\" type=\"radio\" value=\"" + radio.key + '" ' + (this.disabled ? 'readonly' : '') + '>';
      radio_html += "  <label for=\"" + name + "\"></label>" + radio.value + "</label>";
      radio_html += "</div>";
    }
    return radio_html;
  };

  this.attach = function (event, callback) {
    this.events[event] = callback;
  }

  this.rebind = function () {
    var context = this;
    jQuery.each(this.events, function (event, callback) {
      context._get_input_field().unbind(event).bind(event, callback);
    });
  }

  this.check_exists = function(){
    console.log("Check exists search: " + this._get_mass_selector());
    return this._get_input_field().length > 0;
  }

  this.update = function(parent_element, html){
    if(typeof(html) == 'undefined'){
      html = this.html();
    }
    if(this.check_exists()){
      console.log('Updating Field ' + this.name + '.');
      var field = this._get_input_field();
      var value = field.val();
      var options = jQuery('option', field);
      field.closest('.form_row').replaceWith(html);
      jQuery('option', this._get_input_field()).remove();
      this._get_input_field().append(options);
      this._get_input_field().val(value);
    }else{
      console.log('Creating Field ' + this.name + '.');
      parent_element.append(html);
    }
  }

}

function magic_form_group(name, label) {
  this.name = name;
  this.label = label;
  this.fields = [];
  this.add_field = function (field) {
    this.fields.push(field);
    return this;
  };
  this.html = function () {
    return '' +
      '<div class="form_group field-' + this.name + '">' +
      '<h3>' + this.label + '</h3>' +
      '<div class="group-inside">' + this.get_fields_html() + '</div>' +
      '</div>'

  };
  this.get_fields_html = function () {
    var html = '';
    var field;
    while (field = this.fields.shift()) {
      html += field.html();
    }
    return html;
  };
}

var magic_form = {
  name: '',
  label: '',
  value: '',
  form_input: function (name, label, value) {
    if (typeof(value) == 'undefined') {
      value = '';
    }
    this.name = name;
    this.label = label;
    this.value = value;
    return this;
  },
  form_group: function (name, label) {
    return new magic_form_group(name, label);
  },
  process_child_fields: function(field){
    var context = this;

    // Calculate the parents selector
    var parent_selector;

    if(field.type == 'magic_form_group'){
      parent_selector = ".form_group.field-" + field.classes.join('.field-');
    } else if (!typeof(field.classes) == 'undefined'){
      parent_selector = field.classes.join('.');
    } else if (typeof(field.name) == 'string'){
      parent_selector = 'input[name="' + field.name + '"], select[name="' + field.name + '"]';
    }
    var parent_element = jQuery(parent_selector);
    jQuery.each(field.fields, function (i, element){
      //console.log("Process " + element.name);
      //console.log(element);
      /* @var child_field magic_form_item */
      var child_field = context.process_element_to_field(element);

      child_field.update(parent_element, element.html);

      // Handle child fields
      if(element.fields != null){
        context.process_child_fields(element);
      }
    });
  },
  process_element_to_field: function(element){
    var field = new magic_form_field(element.type);
    field.name = element.name;
    field.label = element.label;
    field.disabled = element.disabled;
    field.value = element.value;
    if (element.default_value != null) {
      field.default_value = element.default_value;
    }

    if (typeof(element.options) !== 'undefined' && element.options !== null) {
      if(element.options.length > 0){
        jQuery.each(element.options, function (k, v) {
          field.add_option(k, v);
        });
      }
    }

    return field;
  },
  parse_from_json: function (form, json) {
    this.process_child_fields(json);
  },
  parse_magic_form_json: function(form, json_encoded_magic_form){
    var context = this;
    console.log(json_encoded_magic_form, "Parse magic_form from JSON");
    jQuery.each(json_encoded_magic_form.fields, function(i, field){
      context.process_child_fields(field);
    });
  }
}