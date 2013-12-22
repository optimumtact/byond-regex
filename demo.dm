mob
	var/expression = "(\[A-Z\])(\[a-z\]+)"
	var/format = "sss"
	/*
		This default expression works for anything from:
			foo = bar
		to:
			foo=bar
		to:
			foo=          bar
	*/

	var/datum/regex/results

	verb
		set_expression()
			var/t = input(usr,"Input Expression","title",expression) as text|null
			if(t != null)
				expression = t
				usr << "Expression set to:\t[html_encode(t)]"

		set_format()
			var/t = input(usr,"Input Formatter","title",format) as text|null
			if(t != null)
				format = t
				usr << "Format set to:\t[html_encode(t)]"

		compare_casesensitive(t as text)
			results = regEx_compare(t, expression)
			results.report()

		compare(t as text)
			results = regex_compare(t, expression)
			results.report()

		find_casesensitive(t as text)
			results = regEx_find(t, expression)
			results.report()

		find(t as text)
			results = regex_find(t, expression)
			results.report()

		replaceall_casesensitive(t as text)
			usr << regEx_replaceall(t, expression, format)

		replaceall(t as text)
			usr << regex_replaceall(t, expression, format)

		replace_casesensitive(t as text)
			usr << html_encode(regEx_replace(t, expression, format))

		replace(t as text)
			usr << regex_replace(t, expression, format)

		findall(t as text)
			results = regex_findall(t, expression)
			results.report()

		findall_casesensitive(t as text)
			results = regEx_findall(t, expression)
			results.report()

#define KEYWORD "\[\\Q+-\\E\]\[a-z@\]+"
#define RANKNAME "\\<\[\\w \]+\\>"
		testparse()
			var/datum/regex/Rgx = regex_findall(file2text("map.dmm"),"\\(1,1,\[0-9\]+\\) = \\{\"\\n((\[a-z\]+\\n)+)\"\\}")
			world.log << Rgx.report()

/client/verb/mykey()
	world << key