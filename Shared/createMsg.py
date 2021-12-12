import sys
import colorama
from colorama import Fore, Back, Style
import os.path

colorama.init()

class_name = "Unknown"
HEADER_FORMAT = """#ifndef SADZA_{}_HPP
#define SADZA_{}_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"{}

namespace Msg {{
    struct {} {{
        static const MsgType id = MessageType::{};
{}
    }};
    struct {}Resp {{
        static const MsgType id = MessageType::{}Resp;
        MessageResult result;
    }};
}}

sf::Packet &operator<<(sf::Packet &packet, const Msg::{} &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::{} &msg);

sf::Packet &operator<<(sf::Packet &packet, const Msg::{} &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::{} &msg);

#endif //SADZA_{}_HPP
"""
SOURCE_FORMAT = """#include "Network/Messages/{}.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::{} &msg) {{ return packet{}; }}

sf::Packet &operator>>(sf::Packet &packet, Msg::{} &msg) {{ return packet{}; }}
"""
ADD_MSG_FIND = """template <unsigned M, unsigned DUMMY>
        struct Loop {
            static auto execute(sf::Packet & packet) {
                return Loop<M, 0>::execute(packet);
            }
        };"""
ADD_MSG_TEMPLATE = """

        template <unsigned DUMMY>
        struct Loop<MsgType::{}, DUMMY> {{
            static auto execute(sf::Packet & packet) {{
                Msg::{} msg;
                packet >> msg;
                return msg;
            }}
        }};
        
        template <unsigned DUMMY>
        struct Loop<MsgType::{}Resp, DUMMY> {{
            static auto execute(sf::Packet & packet) {{
                Msg::{}Resp msg;
                packet >> msg;
                return msg;
            }}
        }};"""

deleting_msg = False
attribute_list = []
attributes_formatted = ""
includes_formatted = "\n"

allowed_types_std = ["string", "float", "double", "long double"]
allowed_types_sf = ["Int8", "Uint8", "Int16", "Uint16", "Int32", "Uint32", "Int64", "Uint64"]

allowed_types_msg = """
Allowed Types:
Text
    string
    
Floating:
    float
    double
    long double
    
Signed Integers:
    Int8
    Int16
    Int32
    Int64
    
Unsigned Integers:
    Uint8
    Uint16
    Uint32
    Uint64

"""


def file_exists():
    return os.path.isfile("include/Network/Messages/{}.hpp".format(class_name))


def get_attributes():
    global attributes_formatted
    global includes_formatted

    attributes = {}
    includes = set()

    abort_keywords = ["exit", "cancel", "stop"]
    print("{}Creating message: {} {}{}".format(Back.YELLOW, Fore.GREEN, class_name, Fore.RESET, Back.YELLOW))
    print("{}Type {} to abort.{}".format(Back.RED, abort_keywords, Back.RESET))
    while True:
        ftype = input("Enter field type:\n> ")
        if ftype == "":
            break

        if ftype.lower() in abort_keywords:
            print("{}Message not created: {}".format(Fore.RED, class_name, Fore.RESET))
            exit(0)

        if ftype in allowed_types_std:
            ftype = "std::" + ftype
            includes.add("#include <string>")
        elif ftype in allowed_types_sf:
            ftype = "sf::" + ftype
            includes.add("#include <SFML/Config.hpp>")
        else:
            print("{}{}Unknown type: `{}`!{} Allowed above.".format(allowed_types_msg, Back.RED, ftype, Back.RESET))
            continue

        fname = input("Enter field name:\n> ")

        if fname in attributes:
            print("{}Field with name `{}` already exists. Field not added.{}".format(Fore.RED, fname, Fore.RESET))
            continue

        attributes[fname] = ftype
        attribute_list.append(fname)
        print("{}Field added successfuly{}: {} {};".format(Fore.GREEN, Fore.RESET, ftype, fname))

    for k, v in attributes.items():
        attributes_formatted = attributes_formatted + "        {} {};\n".format(v, k)

    for k in includes:
        includes_formatted = includes_formatted + "{}\n".format(k)


def parse_argument():
    global class_name
    global deleting_msg
    argc = len(sys.argv)
    if argc == 1:
        print("{}Enter message name as first argument!{}".format(Fore.RED, Fore.RESET))
        return False

    first_arg = str(sys.argv[1])
    if first_arg == "-D":
        deleting_msg = True
        if argc < 3:
            print("{}Argument -d requires mesage name!{}".format(Fore.RED, Fore.RESET))
            return False
        class_name = str(sys.argv[2])
    else:
        class_name = str(sys.argv[1])

    return True


def create_class_header():
    global class_name
    global HEADER_FORMAT
    global includes_formatted
    global attributes_formatted
    with open("include/Network/Messages/{}.hpp".format(class_name), "w+") as file:
        file.write(HEADER_FORMAT.format(class_name.upper(), class_name.upper(), includes_formatted,  # Header
                                        class_name, class_name, attributes_formatted,  # Req
                                        class_name, class_name,  # Resp
                                        class_name, class_name, class_name, class_name,  # Packet
                                        class_name.upper()))


def create_class_source():
    global class_name
    global SOURCE_FORMAT
    global attribute_list

    packet_op = ""
    if len(attribute_list):

        for attribute in attribute_list:
            packet_op = packet_op + " op " + "msg." + attribute

    with open("src/Network/Messages/{}.cpp".format(class_name), "w+") as file:
        file.write(SOURCE_FORMAT.format(class_name,
                                        class_name, packet_op.replace("op", "<<"),
                                        class_name, packet_op.replace("op", ">>")))


def add_msg_type():
    global class_name
    with open("include/Network/Messages/Base/MessageType.hpp", "r+") as file:
        content = file.read()
        content = content.replace("OutOfRange", "{},\n        OutOfRange".format(class_name))
        file.seek(0)
        file.write(content)


def add_msg_creator():
    global class_name

    with open("include/Network/Messages/Base/MsgCreator.hpp", "r+") as file:
        content = file.read()
        pos = content.find(ADD_MSG_FIND) + len(ADD_MSG_FIND)
        content = content[:pos] \
                  + ADD_MSG_TEMPLATE.format(class_name, class_name, class_name, class_name) \
                  + content[pos:]

        file.seek(0)
        file.write(content)


def add_include():
    global class_name

    with open("include/Network/Messages/Base/AllMessages.hpp", "r+") as file:
        content = file.read()
        pos = content.find("#endif //SADZA_ALLMESSAGES_HPP") - 1
        content = content[:pos] + '#include "Network/Messages/{}.hpp"\n'.format(class_name) + content[pos:]

        file.seek(0)
        file.write(content)


def delete_header():
    os.remove("include/Network/Messages/{}.hpp".format(class_name))


def delete_source():
    os.remove("src/Network/Messages/{}.cpp".format(class_name))


def delete_msg_type():
    global class_name

    content = None
    with open("include/Network/Messages/Base/MessageType.hpp", "r") as file:
        content = file.read()

    content = content.replace("        {},\n".format(class_name), "")
    with open("include/Network/Messages/Base/MessageType.hpp", "w") as file:
        file.write(content)


def delete_msg_creator():
    global class_name

    content = None
    with open("include/Network/Messages/Base/MsgCreator.hpp", "r") as file:
        content = file.read()

    content = content.replace(ADD_MSG_TEMPLATE.format(class_name, class_name), "")
    with open("include/Network/Messages/Base/MsgCreator.hpp", "w") as file:
        file.write(content)


def delete_include():
    global class_name

    content = None
    with open("include/Network/Messages/Base/AllMessages.hpp", "r") as file:
        content = file.read()

    content = content.replace("#include \"{}.hpp\"\n".format(class_name), "")
    with open("include/Network/Messages/Base/AllMessages.hpp", "w") as file:
        file.write(content)


def main_delete():
    delete_header()
    delete_source()
    delete_msg_type()
    delete_msg_creator()
    delete_include()


def main_create():
    get_attributes()
    create_class_header()
    create_class_source()
    add_msg_type()
    add_msg_creator()
    add_include()


if __name__ == "__main__":

    if parse_argument():
        if deleting_msg:
            if not file_exists():
                print("{}Message not exists: {}{}".format(Fore.RED, class_name, Fore.RESET))
                exit(1);
            main_delete()
            exit(0)

        if file_exists():
            print("{}Message already exists: {}{}".format(Fore.RED, class_name, Fore.RESET))
            exit(1);

        main_create()
