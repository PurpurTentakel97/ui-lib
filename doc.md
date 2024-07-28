| Doc             | Description                                                 |
|-----------------|-------------------------------------------------------------|
| ///<            | Public or protected fields                                  |
| @tparam         | Parameter of a template.                                    |
| @param[in]      | Parameter of a function. It as in parameter                 |
| @param[out]     | Parameter of a function. It is used a out parameter         |
| @param[in, out] | Parameter of a function. It is used as in and out parameter |
| @returns        | Return value                                                |
| @throws         | With exception an when its thrown                           |
| @relatesalso    | used by free-functions to show a related class              |
| @see            | gives additional infos in any kind; eg. a Link              |


Example:
````cpp
/**
 * Sum numbers in a vector.
 *
 * @param values Container whose values are summed.
 * @return sum of `values`, or 0.0 if `values` is empty.
 */
double sum(std::vector<double> & const values) {
    ...
}
````
