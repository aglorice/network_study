//
// Created by aglorice on 2025/12/17.
//

#include "option.h"

using namespace  yazi::utility;


void Option::add(const std::string &opt, Type type) {
    m_opts[opt] = type;
}

Option::Type Option::type(const std::string &opt) const {
    const auto it = m_opts.find(opt);
    if (it == m_opts.end()) {
        return OPT_UNKNOWN;
    }
    return it->second;
}

void Option::parse(int argc, char *argv[]) {
    for (int i = 1;i<argc;i++) {
        std::string arg = argv[i];
        if (arg.substr(0,1) != "-") {
            // 普通参数
            continue;
        }
        if (arg.substr(0,2) == "--") {
            // 长参数
            std::string str = arg.substr(2);
            auto pos = str.find('=');
            if (pos != std::string::npos) {
                // 出现等号
                std::string opt = str.substr(0,pos);
                std::string val = str.substr(pos+1);
                switch (type(opt)) {
                    case OPT_NO: {
                        throw std::logic_error("no argument option: " + opt);
                    }
                    case OPT_OPTIONAL:
                    case OPT_REQUIRED: {
                        m_args[opt] = val;
                        break;
                    }
                    default:
                        break;
                }
            }else {
                // 没有出现 = 号
                switch (type(str)) {
                    case OPT_NO:
                    case OPT_OPTIONAL: {
                        m_args[str] = "";
                        break;
                    }
                    case OPT_REQUIRED: {
                        if (i + 1> argc) {
                            throw std::logic_error("option required argument: " + str);
                        }
                        std::string val = argv[i+1];
                        if (val.substr(0,1) == "-") {
                            throw std::logic_error("option missing argument :" + str);
                        }
                        m_args[str] = val;
                        i++; // 跳过下一个参数
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        else {
            // 短参数
            std::string opt = arg.substr(1,1);
            switch (type(opt)) {
                case OPT_NO: {
                    if (arg.length() >=2) {
                        // 合并参数
                            for (int k = 1;k<arg.length();k++) {
                                std::string o(1,arg[k]);
                                if (type(o) != OPT_NO) {
                                    continue;
                                }
                                m_args[o] = "";
                            }
                    }
                    break;
                }
                case OPT_OPTIONAL: {
                    if (arg.length() > 2) {
                        m_args[opt] = arg.substr(2);
                    }else {
                        m_args[opt] = "";
                    }
                    break;
                }
                case OPT_REQUIRED: {
                    if (i+1 > argc) {
                        throw std::logic_error("option required argument : " + opt);
                    }
                    std::string val = argv[i+1];
                    if (val.substr(0,1) == "-") {
                        throw std::logic_error("option missing argument: " + opt);
                    }
                    m_args[opt] = val;
                    i++;
                    break;
                }
                default:
                    break;
            }
        }
    }
}


void Option::show() const {
    for (const auto &pair : m_args) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}


bool Option::has(const std::string &opt) const {
    auto it = m_opts.find(opt);
    if (it == m_opts.end()) {
        return false;
    }
    return m_args.find(opt) == m_args.end();
}

Value Option::get(const std::string &opt) {
    auto it = m_opts.find(opt);
    if (it == m_opts.end()) {
        return Value("");
    }
    switch (it->second) {
        case OPT_NO: {
            return Value(m_args.find(opt) != m_args.end());
        }
        case OPT_OPTIONAL:
        case OPT_REQUIRED: {
            return Value(m_args[opt]);
        }
        default:
            return Value("");
    }
}
