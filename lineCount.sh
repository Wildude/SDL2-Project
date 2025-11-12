find . -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.lua" \) \
! -name "base64.cpp" \
! -name "base64.hpp" \
! -name "cmdinfo.hpp" \
! -name "Ginfo.hpp" \
! -name "tinyxml2.cpp" \
! -name "tinyxml2.hpp" | xargs wc -l
# oneline
find . -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.lua" \) ! -name "base64.cpp" ! -name "base64.hpp" ! -name "cmdinfo.hpp" ! -name "Ginfo.hpp" ! -name "tinyxml2.cpp" ! -name "tinyxml2.hpp" | xargs wc -l

