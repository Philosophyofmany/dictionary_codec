### Query Performance Analysis

| Query Type              | Query Term   | Indices | Time (µs) |
|-------------------------|--------------|---------|-----------|
| **Exact Match Vanilla** | uyadc        | 357     | 22 µs     |
| **Exact Match Vanilla** | ikjsyqehs    | 818     | 26 µs     |
| **Exact Match Vanilla** | yafcyuc      | 958     | 26 µs     |
| **Exact Match Vanilla** | odbeyulzt    | 135     | 23 µs     |
| **Exact Match Vanilla** | wzmbpd       | 18      | 29 µs     |
| **Exact Match Vanilla** | edwdyswjf    | 945     | 26 µs     |
| **Exact Match Vanilla** | vbtjs        | 554     | 26 µs     |
| **Exact Match Vanilla** | mzsirlq      | 93      | 26 µs     |
| **Exact Match Vanilla** | qwlarkmbw    | 967     | 28 µs     |
| **Exact Match No SIMD** | uyadc        | 357     | 3 µs      |
| **Exact Match No SIMD** | ikjsyqehs    | 818     | 4 µs      |
| **Exact Match No SIMD** | yafcyuc      | 958     | 4 µs      |
| **Exact Match No SIMD** | odbeyulzt    | 135     | 3 µs      |
| **Exact Match No SIMD** | wzmbpd       | 18      | 3 µs      |
| **Exact Match No SIMD** | edwdyswjf    | 945     | 3 µs      |
| **Exact Match No SIMD** | vbtjs        | 554     | 3 µs      |
| **Exact Match No SIMD** | mzsirlq      | 93      | 3 µs      |
| **Exact Match No SIMD** | qwlarkmbw    | 967     | 3 µs      |
| **Prefix Match Vanilla**| uya          | 357     | 27 µs     |
| **Prefix Match Vanilla**| ikj          | 818     | 30 µs     |
| **Prefix Match Vanilla**| yaf          | 958     | 39 µs     |
| **Prefix Match Vanilla**| odb          | 135     | 23 µs     |
| **Prefix Match Vanilla**| wzm          | 18      | 26 µs     |
| **Prefix Match Vanilla**| edw          | 945     | 38 µs     |
| **Prefix Match Vanilla**| vbt          | 554     | 31 µs     |
| **Prefix Match Vanilla**| mzs          | 93      | 33 µs     |
| **Prefix Match Vanilla**| qwl          | 967     | 23 µs     |
| **Prefix Match No SIMD**| uya          | 357     | 23 µs     |
| **Prefix Match No SIMD**| ikj          | 818     | 24 µs     |
| **Prefix Match No SIMD**| yaf          | 958     | 22 µs     |
| **Prefix Match No SIMD**| odb          | 135     | 24 µs     |
| **Prefix Match No SIMD**| wzm          | 18      | 22 µs     |
| **Prefix Match No SIMD**| edw          | 945     | 25 µs     |
| **Prefix Match No SIMD**| vbt          | 554     | 22 µs     |
| **Prefix Match No SIMD**| mzs          | 93      | 22 µs     |
| **Prefix Match No SIMD**| qwl          | 967     | 22 µs     |
