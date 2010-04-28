/* Copyright 2008 (C) Nicira, Inc.
 *
 * This file is part of NOX.
 *
 * NOX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * NOX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NOX.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "json-util.hh"
#include <fstream>

using namespace std;

namespace vigil {
    namespace json {
        json_object* load_document(const string& file) {
            
            // TODO: Add checks, return error etc
            int len;
            char* jsonstr;
            ifstream in;
            json_object* jo;
            
            in.open(file.c_str());
            // get conf file len
            in.seekg(0, ios::end);
            len = in.tellg();
            in.seekg(0, ios::beg);
            // alloc
            jsonstr = new char [len];
            in.read(jsonstr,len);
            in.close();
            boost::shared_array<uint8_t> str;
            str.reset(new uint8_t[len+1]);
            strcpy((char *) str.get(),jsonstr);
            jo = new json_object(str.get(), len);
            
            return jo;
        }
        
        json_object* get_dict_value(const json_object* jo, string key){
            //Make sure jo is a dictionary (add)
            json_dict::iterator di;
            json_dict* jodict = (json_dict*) jo->object;
            di = jodict->find(key);
            if (di==jodict->end()) {
                return NULL;
                }
            else {
                return di->second;
                }
        }
    }
}
