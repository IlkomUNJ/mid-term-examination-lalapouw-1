Ukuran Jendela Ideal: 15×15
Ukuran jendela 15×15 dipilih karena merupakan ukuran terkecil yang secara konsisten mampu membingkai seluruh segmen (titik biru) dengan ruang kosong seminimal mungkin. Ukuran ini kemudian ditetapkan sebagai Ukuran Jendela Ideal, karena menyeimbangkan kelengkapan segmen dan efisiensi komputasi.
Pola Deteksi Segmen:
Segmen diidentifikasi menggunakan Pola Kepadatan Piksel (Density Pattern). Sebuah jendela 15×15 dianggap sebagai segmen valid jika di dalamnya terdapat lebih dari 20 piksel non-putih (piksel yang termasuk segmen). Titik biru sebagai target merupakan objek kecil dan padat. Ambang batas 20 piksel dipilih berdasarkan percobaan, sehingga dapat membedakan dengan jelas antara kepadatan titik biru (>20 piksel non-putih) dan noise atau area kosong (<20 piksel non-putih).

Ukuran Jendela 10×10: Tidak Ideal
Percobaan dengan jendela 10×10 menunjukkan bahwa ukuran ini tidak cocok untuk mendeteksi segmen titik biru.
Masalah Utama: Underfitting (Terlalu Kecil)
Pola Deteksi Salah:
Sebagian besar kotak hijau (yang seharusnya menandai titik biru) tampak tidak terpusat di titik biru atau hanya menutupi salah satu tepinya.
Segmentasi Gagal:
Banyak titik biru di kanvas yang tidak terdeteksi sama sekali.
Hal ini terjadi karena diameter titik biru biasanya lebih besar dari 10 piksel.
Jendela 10×10 yang digeser di kanvas tidak mampu menangkap seluruh kepadatan titik biru, sehingga tidak memenuhi ambang batas 20 piksel non-putih.

Perubahan yang dilakukan pada code:
1. Penambahan fungsi segmentDetection()
    Tujuannya untuk scan seluruh canvas dan deteksi window 10×10 yang punya piksel non-putih (artinya ada garis/titik). Kodenya pakai loop dua lapis (i, j) dan dua lapis lagi di dalam (m, n) buat baca tiap window 10×10 dari QImage.
2.  Penambahan logika deteksi piksel (int threshold)
3.  Penambahan visualisasi hasil (pakai QLabel & QPainter)
4.  Perubahan pada CustomMatrix