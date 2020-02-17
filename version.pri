#
# Please prepare the following variables in advance.
#
# TargetProduct
# TargetDescription
# TargetVersion
# TargetCompany
# TargetDomain
# TargetCopyright
#

#
# QMAKE_TARGET
#
QMAKE_TARGET_PRODUCT = $$TargetProduct
QMAKE_TARGET_DESCRIPTION = $$TargetDescription
QMAKE_TARGET_COMPANY = $$TargetCompany
QMAKE_TARGET_COPYRIGHT = $$TargetCopyright

#
# VERSION
#
VERSION = $$TargetVersion
ParsedVersion = $$split(TargetVersion, ".")
VER_MAJ = $$member(ParsedVersion, 0)
VER_MIN = $$member(ParsedVersion, 1)
VER_PAT = $$member(ParsedVersion, 2)

#
# QCoreApplication Properties
#
DEFINES += PROJECT_PRODUCT=$$join(TargetProduct, +)
DEFINES += PROJECT_COMPANY=$$join(TargetCompany, +)
DEFINES += PROJECT_DOMAIN=$$TargetDomain
DEFINES += PROJECT_VERSION=$$TargetVersion
DEFINES += PROJECT_VER_MAJ=$$VER_MAJ
DEFINES += PROJECT_VER_MIN=$$VER_MIN
DEFINES += PROJECT_VER_PAT=$$VER_PAT
