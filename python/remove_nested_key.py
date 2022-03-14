"""
user:~$ pytest remove_nested_key
"""


def remove_nested_key(key, obj, fields, path=""):
    """
    Remove key from nested dictionary
    Args:
        key (str):
        obj (dict|list): [in/out] structure from which the key will be removed
        fields (set): [out] set of removed key paths
        path (list[str]): current path to key
    """
    if key is None or fields is None:
        return

    if isinstance(obj, dict):
        for k in list(obj.keys()):
            if key == k:
                obj.pop(key)
                fields.add(path + key)
            else:
                remove_nested_key(key, obj[k], fields, path + k + ".")

    if isinstance(obj, list):
        for item in obj:
            remove_nested_key(key, item, fields, path + "[].")


def test_remove_none():
    remove_nested_key(None, {"k": ""}, set())


def test_remove_empty():
    remove_nested_key("k", {}, set())
    remove_nested_key("k", [], set())


def test_remove_key():
    data = {"k": "", "a": ""}
    restricted = set()
    remove_nested_key("k", data, restricted)
    assert data == {"a": ""}
    assert restricted == set(["k"])


def test_remove_key_not_found():
    data = {"a": "", "b": ""}
    restricted = set()
    remove_nested_key("k", data, restricted)
    assert data == {"a": "", "b": ""}
    assert restricted == set()


def test_remove_key_from_nested_dict():
    data = {"a": {"b": {"k": "", "c": ""}}}
    restricted = set()
    remove_nested_key("k", data, restricted)
    assert data == {"a": {"b": {"c": ""}}}
    assert restricted == set(["a.b.k"])


def test_remove_keys_from_nested_dicts():
    data = {"k": "", "a": {"k": ""}}
    restricted = set()
    remove_nested_key("k", data, restricted)
    assert data == {"a": {}}
    assert restricted == set(["k", "a.k"])


def test_remove_keys_from_nested_lists_and_dicts():
    data1 = [
        {"a": "", "k": ""},
        [{"k": {}}, "k", {"b": {"k": ""}}]
    ]
    restricted1 = set()
    remove_nested_key("k", data1, restricted1)
    assert data1 == [{"a": ""}, [{}, "k", {"b": {}}]]
    assert restricted1 == set(["[].k", "[].[].k", "[].[].b.k"])

    data2 = {"a": ["k", {"b": [{"k": ""}, []]}], "k": ""}
    restricted2 = set()
    remove_nested_key("k", data2, restricted2)
    assert data2 == {"a": ["k", {"b": [{}, []]}]}
    assert restricted2 == set(["a.[].b.[].k", "k"])

    data3 = [
        [{"k": ""}, {"a": ""}],
        [{"b": ""}, {"k": ""}]
    ]
    restricted3 = set()
    remove_nested_key("k", data3, restricted3)
    assert data3 == [[{}, {"a": ""}], [{"b": ""}, {}]]
    assert restricted3 == set(["[].[].k"])
