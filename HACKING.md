# Working on schroot

A short guide to the conventions used in the schroot project.


## Building from git

First, clone the git repositories:

```
% git clone https://github.com/codelibre-net/schroot.git
% cd schroot
```


## Coding style

The style should be apparent from the source.  It is the default Emacs
`c++-mode` style, with paired brackets aligned vertically.

- Use `nullptr` rather than `NULL`.
- Use C++ casts rather than C-style casts.
- Don't use `void *` unless there is no alternative.
- Add Doxygen comments for everything; use `EXTRACT_ALL = NO` in
  `doc/schroot.dox` to check for missing or incomplete documentation.

## Format strings

The sources use `boost::format` for type-safe formatted output.  Make
sure that the maximum number of options passed is the same as the
highest `%n%` in the format string.  UTF-8 string literals are used in
the sources.

The following styles are used:

Style        | Formatting    | Syntax
-------------|---------------|-------
Values       | Single quotes | `‘’`
Example text | Double quotes | `“”`
User input   | Double quotes | `“”`

## Documentation

All the documentation is in UNIX manual page format.  GNU roff
(`groff`) extensions are permitted, as is use of `tbl`.  Make sure the
printed output is as good as terminal display.  Run `make ps` or `make
pdf` to build the printed documentation.

The following styles are used:

Style                 | Formatting               | Syntax
----------------------|--------------------------|----------------------
New term              | Bold                     | `.B or \fB`
Option definition     | Bold, args in italic     | `.BR and \fI`
Option reference      | Italic                   | `.I or \fI`
File definition       | Bold italic              | `\f[BI]`
File reference        | Italic                   | `.I or \fI`
Config key definition | Courier bold italic      | `\f[CBI]`
Config key reference  | Courier italic           | `\f[CI]`
Values                | Single quotes            | `\[oq] and \[cq]`
Example text          | Double quotes            | `\[lq] and \[rq]`
Cross references      | Italics in double quotes | `\[lq]\fI...\fP\[rq]`
Verbatim examples     | Courier                  | `\f[CR]`
Verbatim user input   | Courier bold             | `\f[CB]`

## Releasing

### Test conformance

The code must pass the testsuite:

```
% fakeroot ctest -V
```

It must also pass some tests which must be run by hand:

### Chdir fallback behaviour

Fallback behaviour has been documented in the manual pages.

Note that `--debug=notice` will show the internal fallback list
computed for the session.

### Setup script behaviour

To check if process termination works:

```
schroot -v -c sid -- sh -c "trap '' INT; trap '' TERM; sleep 2 &"
```

To check if process killing works:

```
schroot -v -c sid -- sh -c "trap '' INT; trap '' TERM; sleep 20 &"
```

### Release process

In order to make a release, the following must be done:

- Use a fresh clone or make sure the tree is pristine
- Make sure all generated files are up to date.  Run `make`
  and/or `make update-po` to update all translations.
  Commit any changes.
- Create a signed release tag `release/schroot-$version`
- Push all branches and tags to the correct places:

  ```
  % git push origin $branch
  % git push origin release/schroot-$version
  ```
- Make release on GitLab
