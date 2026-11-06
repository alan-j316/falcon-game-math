set(FALCON_CORE_TARGET_NAME FalconCore${FALCON_INTERNAL_TARGET_SUFFIX})
add_library(${FALCON_CORE_TARGET_NAME} INTERFACE
        traits/TypeHelpers.h

        Preprocessors.h
        DoxygenGroups.h
)
target_compile_features(${FALCON_CORE_TARGET_NAME}  INTERFACE cxx_std_20)

# TODO: Remove internal target linkages(as this can fail on builds not running in strict mode)
target_link_libraries(${FALCON_CORE_TARGET_NAME} INTERFACE
        ${PROJECT_NAME}-StrictWarnings
        ${PROJECT_NAME}-ProjectSanitizers
)

target_include_directories(${FALCON_CORE_TARGET_NAME} INTERFACE ${FALCON_LIBRARY_ROOT_DIR})