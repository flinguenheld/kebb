##### Debian:

1. List dependencies:  
   `dpkg-shlibdeps -O kebb`

2. Strip:  
   `strip kebb`

3. Remove runpaths:  
   `chrpath -d kebb`

4. Create .deb:  
   `dpkg-deb --root-owner-group --build kebb`

5. Check:  
   `lintian kebb.deb`

#### Arch:

1. List dependencies:  
   `readelf -d kebb | grep NEEDED`
   `find-libdeps .tar.gz`

2. Create .zst
   `makepkg`