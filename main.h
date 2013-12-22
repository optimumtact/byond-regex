/*
	This file is part of bygex.

    bygex is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

    bygex is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with bygex.  If not, see <http://www.gnu.org/licenses/>

    6-Oct-2013 - carnie (elly1989@rocketmail.com), accreditation appreciated but not required.
    Please do not remove this comment.
*/

#ifndef MAIN_H
#define MAIN_H
#endif // MAIN_H

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#if defined(BUILD_DLL)
	#define EXPORT __declspec(dllexport)
#else
    #define EXPORT __declspec(dllimport)
#endif

char EXPORT *regEx_compare(int argc, char *argv[]);
char EXPORT *regex_compare(int argc, char *argv[]);

char EXPORT *regEx_find(int argc, char *argv[]);
char EXPORT *regex_find(int argc, char *argv[]);
char EXPORT *regEx_findall(int argc, char *argv[]);
char EXPORT *regex_findall(int argc, char *argv[]);

char EXPORT *regEx_replace(int argc, char *argv[]);
char EXPORT *regex_replace(int argc, char *argv[]);
char EXPORT *regEx_replaceall(int argc, char *argv[]);
char EXPORT *regex_replaceall(int argc, char *argv[]);
char EXPORT *regEx_replaceallliteral(int argc, char *argv[]);
char EXPORT *regex_replaceallliteral(int argc, char *argv[]);

#ifdef __cplusplus
}
#endif // __cplusplus
