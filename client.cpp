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

#include <stdio.h>
#include <string>
#include "main.h"

int main(void)
{
    char buffer[100];
    char buffer2[100];
    sprintf(buffer, "%s", "this subject has a submarine as a subsequence");
    sprintf(buffer2, "s");
    char *args[2] = {buffer, buffer2};
    char* result = regEx_find(2, args);
    printf("str: %s\nexpression: %s\nResult: %s\n", buffer, buffer2, result);
    return 0;
}
