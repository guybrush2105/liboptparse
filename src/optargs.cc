/* liboptparse is a library used to handle command line options.
 * Copyright (C) 2019 Guybrush aka Gabriele Labita
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <string>
#include <sstream>
#include <cassert>
#include <locale>

#include "liboptparse/utils.hh"
#include "liboptparse/optargs.hh"

OptionArgumentValue::OptionArgumentValue()
    :_value("") { }

OptionArgumentValue::OptionArgumentValue(const std::string& value)
    : _value(value) { }

OptionArgumentValue::OptionArgumentValue(
    const OptionArgumentValue& option_argument_value)
    : _value(option_argument_value._value) { }


OptionArgumentValue::OptionArgumentValue(
    const OptionArgumentValue&& option_argument_value)
    : _value(std::move(option_argument_value._value)) { }


OptionArgumentValue::~OptionArgumentValue() { }

const std::string& OptionArgumentValue::get_value() const noexcept {
    return _value;
}

OptionArgumentValue::operator bool() const {
    bool t = false;
    if (!_value.empty()) {
        std::stringstream ss(_value);
        ss >> std::boolalpha >> t;
    }
    return t;
}

OptionArgumentValue::operator int() const {
    int v;
    std::stringstream ss(_value);
    ss >> v;
    return v;
}

OptionArgumentValue::operator short() const {
    short v;
    std::stringstream ss(_value);
    ss >> v;
    return v;
}

OptionArgumentValue::operator long() const {
    long v;
    std::stringstream ss(_value);
    ss >> v;
    return v;
}

OptionArgumentValue::operator unsigned short() const {
    unsigned short v;
    std::stringstream ss(_value);
    ss >> v;
    return v;
}

OptionArgumentValue::operator unsigned long() const {
    unsigned long v;
    std::stringstream ss(_value);
    ss >> v;
    return v;
}

OptionArgumentValue::operator unsigned int() const {
    unsigned int v;
    std::stringstream ss(_value);
    ss >> v;
    return v;
}

OptionArgumentValue::operator float() const {
    float v;
    std::stringstream ss(_value);
    ss >> v;
    return v;
}

OptionArgumentValue::operator double() const {
    double v;
    std::stringstream ss(_value);
    ss >> v;
    return v;
}

OptionArgumentValue::operator std::string() const {
    return get_value();
}


bool operator==(const OptionArgumentValue& first,
                const OptionArgumentValue& second) {
    return first.get_value() == second.get_value();
}

bool operator!=(const OptionArgumentValue& first,
                const OptionArgumentValue& second) {
    return !(first == second);
}

std::ostream& operator<<(std::ostream& os,
                         const OptionArgumentValue& value) {
    os << value.get_value();
    return os;
}


class OptionArgument::Impl {
public:
    explicit Impl(char short_name)
        : _short_name(short_name) {
        assert(OK());
    }

    Impl(char short_name,
         const std::string& long_name)
        : _short_name(short_name), _long_name(long_name) {
        assert(OK());
    }

    Impl(const Impl& impl)
        : _short_name(impl._short_name),
          _long_name(impl._long_name),
          _help(impl._help),
          _default_value(impl._default_value),
          _metavar(impl._metavar),
          _type(impl._type){
        assert(impl.OK());    
        assert(OK());
    }

    const std::string& get_default_value() const noexcept {
        return _default_value;
    }

    void set_default_value(
        const std::string& default_value) noexcept {
        _default_value = default_value;
    }

    const std::string& get_help() const noexcept {
        return _help;
    }

    void set_help(const std::string& help) noexcept {
        _help = help;
    }

    const std::string& get_long_name() const noexcept {
        assert(OK());
        return _long_name;
    }
    
    char get_short_name() const noexcept {
        assert(OK());
        return _short_name;
    }

    const std::string& get_metavar() const noexcept {
        return _metavar;
    }

    void set_metavar(const std::string& metavar) noexcept {
        _metavar = metavar;
    }
    
    OptionArgumentType get_type() const noexcept {
        return _type;
    }

    void set_type(OptionArgumentType type) noexcept {
        _type = type;
    }

private:
    bool OK() const {
        return _LIBOPTPARSE_::is_valid_short_name(_short_name) &&
            _LIBOPTPARSE_::is_valid_long_name(_long_name);
    }

    char               _short_name;
    std::string        _long_name;
    std::string        _help;
    std::string        _default_value;
    std::string        _metavar;
    OptionArgumentType _type = OptionArgumentType::value;
};


OptionArgument::OptionArgument(char short_name)
    : _pimpl(new Impl(short_name)) {
}

OptionArgument::OptionArgument(
    char short_name,
    const std::string& long_name)
    : _pimpl(new Impl(short_name, long_name)) { }

OptionArgument::OptionArgument(const OptionArgument& option_argument)
    : _pimpl(new Impl(*option_argument._pimpl)) { }

OptionArgument::OptionArgument(OptionArgument&& option_argument)
    : _pimpl(std::move(option_argument._pimpl)) { }

OptionArgument::~OptionArgument() { }

char OptionArgument::get_short_name() const noexcept {
    return _pimpl -> get_short_name();
}

const std::string& OptionArgument::get_long_name() const noexcept {
    return _pimpl -> get_long_name();
}

const std::string& OptionArgument::get_help() const noexcept {
    return _pimpl -> get_help();
}

OptionArgument& OptionArgument::set_help(
    const std::string& help) noexcept {
    _pimpl -> set_help(help);
    return *this;
}

const std::string&
OptionArgument::get_default_value() const noexcept {
    return _pimpl -> get_default_value();
}

OptionArgument& OptionArgument::set_default_value(
    const std::string& default_value) noexcept {
    _pimpl -> set_default_value(default_value);
    return *this;
}

const std::string& OptionArgument::get_metavar() const noexcept {
    return _pimpl -> get_metavar();
}

OptionArgument& OptionArgument::set_metavar(
    const std::string& metavar) noexcept {
    _pimpl -> set_metavar(metavar);
    return *this;
}

OptionArgumentType OptionArgument::get_type() const noexcept {
    return _pimpl -> get_type();
}

OptionArgument& OptionArgument::set_type(
    OptionArgumentType type) noexcept {
    _pimpl -> set_type(type);
    return *this;
}

bool operator==(const OptionArgument& first,
                const OptionArgument& second) {
    return first.get_short_name() == second.get_short_name();
}

bool operator!=(const OptionArgument& first,
                const OptionArgument& second) {
    return !(first == second);
}
