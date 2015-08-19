#!/bin/bash

mv libatomic128.a libatomic128.a.old
sed s/__xync_/__sync_/g < libatomic128.a.old > libatomic128.a
rm libatomic128.a.old
