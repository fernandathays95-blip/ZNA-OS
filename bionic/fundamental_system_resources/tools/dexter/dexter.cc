/*
 * Copyright (C) 2017-2025 ZNA-OS / Example
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      LICENSES/APACHE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <memory>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#ifdef _WIN32
#include <io.h>
#define S_ISREG(mode) (((mode) & _S_IFREG) != 0)
#else
#include <unistd.h>
#endif

// -----------------------------------------------------------------------------
// Mocked Dexter-like tool for ZNA-OS
// This is intentionally standalone and uses different symbol names than AOSP.
// Replace mocks with real dex/IR types when integrating into a full build.
// -----------------------------------------------------------------------------

namespace dexx {
  using u1 = unsigned char;
  using u2 = unsigned short;
  using u4 = unsigned int;

  struct HeaderMock {
    u4 file_size = 0;
    u4 data_size = 0;
    u4 link_size = 0;
    u4 class_defs_size = 0;
    u4 string_ids_size = 0;
    u4 type_ids_size = 0;
    u4 proto_ids_size = 0;
    u4 field_ids_size = 0;
    u4 method_ids_size = 0;
  };

  struct MapItemMock {
    u4 type;
    u4 offset;
    u4 size;
  };

  struct MapListMock {
    std::vector<MapItemMock> list;
    u4 size = 0;
  };

  // Reader mock provides header/map and simple helpers
  class ReaderMock {
    HeaderMock hdr_;
    MapListMock maplist_;
  public:
    ReaderMock(const u1* /*data*/, size_t in_size) {
      hdr_.file_size = static_cast<u4>(in_size);
      hdr_.data_size = static_cast<u4>(in_size / 2);
      hdr_.link_size = 0;
      hdr_.class_defs_size = 3 + (in_size % 7);
      hdr_.string_ids_size = 20 + (in_size % 50);
      hdr_.type_ids_size = 10 + (in_size % 20);
      hdr_.proto_ids_size = 4 + (in_size % 5);
      hdr_.field_ids_size = 15 + (in_size % 30);
      hdr_.method_ids_size = 30 + (in_size % 60);

      maplist_.size = 3;
      maplist_.list = {
        {0x1000, 0x100, 0x10},
        {0x2000, 0x200, 0x20},
        {0x3000, 0x300, 0x30}
      };
    }

    const HeaderMock* Header() const { return &hdr_; }
    const MapListMock* MapList() const { return &maplist_; }

    struct ClassDef { u4 class_idx; };
    std::vector<ClassDef> ClassDefs() const {
      std::vector<ClassDef> v;
      for (u4 i=0;i<hdr_.class_defs_size;i++) v.push_back({i});
      return v;
    }

    struct TypeId { u4 descriptor_idx; };
    std::vector<TypeId> TypeIds() const {
      std::vector<TypeId> v;
      for (u4 i=0;i<hdr_.type_ids_size;i++) v.push_back({i});
      return v;
    }

    const char* GetStringDescriptor(u4 idx) const {
      static std::string s;
      std::stringstream ss;
      ss << "Lznax/os/Class" << idx << ";";
      s = ss.str();
      return s.c_str();
    }

    void CreateFullRepresentation() const { /* mock no-op */ }
    void CreateSingleClassRep(u4 /*class_idx*/) const { /* mock no-op */ }

    std::vector<std::string> MethodHandles() const { return {"mhA","mhB","mhC"}; }
  };
} // namespace dexx

namespace irx {
  struct DexRepresentation {
    std::vector<std::string> strings;
    std::vector<std::string> types;
    std::vector<std::string> protos;
    std::vector<std::string> fields;
    std::vector<std::string> encoded_fields;
    std::vector<std::string> methods;
    std::vector<std::string> encoded_methods;
    std::vector<std::string> classes;
    std::vector<std::string> method_handles;
    std::vector<std::string> type_lists;
    std::vector<std::string> code;
    std::vector<std::string> debug_info;
    std::vector<std::string> encoded_values;
    std::vector<std::string> encoded_arrays;
    std::vector<std::string> annotations;
    std::vector<std::string> annotation_elements;
    std::vector<std::string> annotation_sets;
    std::vector<std::string> annotation_set_ref_lists;
    std::vector<std::string> annotations_directories;
    std::vector<std::string> field_annotations;
    std::vector<std::string> method_annotations;
    std::vector<std::string> param_annotations;
  };
} // namespace irx

// Disassembler mock
class DisasmMock {
public:
  enum class CfgKind { None, Compact, Verbose };
  DisasmMock(std::shared_ptr<const irx::DexRepresentation> /*r*/, CfgKind /*k*/) {}
  void DumpAll() { printf("[disasm-mock] DumpAll called\n"); }
};

namespace experiments_mock {
  void RunExp(const std::string& name, std::shared_ptr<irx::DexRepresentation> repr) {
    printf("[exp-mock] Running '%s'\n", name.c_str());
    (void)repr;
  }
}

// -----------------------------------------------------------------------------
class DexterTool {
public:
  DexterTool(int argc, char** argv) : argc_(argc), argv_(argv) {
    print_stats_ = false;
    verbose_ = false;
    list_classes_ = false;
    disasm_ = false;
    show_map_ = false;
    cfg_mode_ = DisasmMock::CfgKind::None;
    extract_class_name_ = nullptr;
    out_file_name_ = nullptr;
  }

  void PrintUsage() const;
  int Run();

private:
  int argc_;
  char** argv_;
  bool print_stats_;
  bool verbose_;
  bool list_classes_;
  bool disasm_;
  bool show_map_;
  std::vector<std::string> exps_;
  DisasmMock::CfgKind cfg_mode_;
  const char* extract_class_name_;
  const char* out_file_name_;
  const char* dex_path_;

  double t_reader_ = 0.0;
  double t_writer_ = 0.0;
  double t_exps_ = 0.0;

  int ProcessPath();
  bool BuildNewImage(std::shared_ptr<irx::DexRepresentation> rep);
};

static std::string ToDescriptor(const char* name) {
  std::stringstream ss;
  ss << "L";
  for (auto p = name; *p != '\0'; ++p) ss << (*p == '.' ? '/' : *p);
  ss << ";";
  return ss.str();
}

void DexterTool::PrintUsage() const {
  printf("\nZNA-OS dexreport (mock)\n\n");
  printf("dexreport [flags] [-e classname] [-o outfile] <dexfile>\n");
  printf(" -h : help\n");
  printf(" -s : show stats\n");
  printf(" -e : extract class\n");
  printf(" -l : list classes\n");
  printf(" -v : verbose\n");
  printf(" -o : write new .dex\n");
  printf(" -d : disassemble\n");
  printf(" -m : print map\n");
  printf(" --cfg : cfg type (compact|verbose)\n\n");
}

int DexterTool::Run() {
  const std::map<std::string, DisasmMock::CfgKind> cfg_names = {
    {"none", DisasmMock::CfgKind::None},
    {"compact", DisasmMock::CfgKind::Compact},
    {"verbose", DisasmMock::CfgKind::Verbose},
  };

  enum { kCfgOpt = 1 };
  const option long_opts[] = {
    {"cfg", required_argument, 0, kCfgOpt},
    {0,0,0,0}
  };

  bool show_help = false;
  int opt; int optidx = 0;
  while ((opt = ::getopt_long(argc_, argv_, "hlsvdmo:e:x:", long_opts, &optidx)) != -1) {
    switch (opt) {
      case kCfgOpt: {
        auto it = cfg_names.find(::optarg);
        if (it == cfg_names.end()) {
          printf("Invalid --cfg value\n");
          show_help = true;
        } else cfg_mode_ = it->second;
      } break;
      case 's': print_stats_ = true; break;
      case 'v': verbose_ = true; break;
      case 'l': list_classes_ = true; break;
      case 'e': extract_class_name_ = ::optarg; break;
      case 'd': disasm_ = true; break;
      case 'm': show_map_ = true; break;
      case 'o': out_file_name_ = ::optarg; break;
      case 'x': exps_.push_back(::optarg); break;
      case 'h':
      default:
        show_help = true;
        break;
    }
  }

  if (show_help || ::optind + 1 != argc_) {
    PrintUsage();
    return 1;
  }

  dex_path_ = argv_[::optind];
  return ProcessPath();
}

static void PrintMapMock(const dexx::ReaderMock& rdr) {
  printf("\nSections summary: name, offset, size [count]\n");
  const dexx::MapListMock* m = rdr.MapList();
  for (dexx::u4 i = 0; i < m->size; ++i) {
    const dexx::MapItemMock& it = m->list[i];
    const char* nm = "UNKNOWN";
    switch (it.type) {
      case 0x1000: nm = "HeaderSeg"; break;
      case 0x2000: nm = "StringIds"; break;
      case 0x3000: nm = "TypeIds"; break;
      default: nm = "Other";
    }
    dexx::u4 sz = (i == m->size - 1) ? rdr.Header()->file_size - it.offset : m->list[i+1].offset - it.offset;
    printf("  %-25s : %8x, %8x  [%u]\n", nm, it.offset, sz, it.size);
  }
}

static void PrintIrStats(std::shared_ptr<const irx::DexRepresentation> rep) {
  printf("\n.dex IR statistics:\n");
  printf("  strings                       : %zu\n", rep->strings.size());
  printf("  types                         : %zu\n", rep->types.size());
  printf("  protos                        : %zu\n", rep->protos.size());
  printf("  fields                        : %zu\n", rep->fields.size());
  printf("  encoded_fields                : %zu\n", rep->encoded_fields.size());
  printf("  methods                       : %zu\n", rep->methods.size());
  printf("  encoded_methods               : %zu\n", rep->encoded_methods.size());
  printf("  classes                       : %zu\n", rep->classes.size());
  printf("  method_handles                : %zu\n", rep->method_handles.size());
  printf("  type_lists                    : %zu\n", rep->type_lists.size());
  printf("  code                          : %zu\n", rep->code.size());
  printf("  debug_info                    : %zu\n", rep->debug_info.size());
  printf("  encoded_values                : %zu\n", rep->encoded_values.size());
  printf("  encoded_arrays                : %zu\n", rep->encoded_arrays.size());
  printf("  annotations                   : %zu\n", rep->annotations.size());
  printf("  annotation_elements           : %zu\n", rep->annotation_elements.size());
  printf("  annotation_sets               : %zu\n", rep->annotation_sets.size());
  printf("  annotation_set_ref_lists      : %zu\n", rep->annotation_set_ref_lists.size());
  printf("  annotations_directories       : %zu\n", rep->annotations_directories.size());
  printf("  field_annotations             : %zu\n", rep->field_annotations.size());
  printf("  method_annotations            : %zu\n", rep->method_annotations.size());
  printf("  param_annotations             : %zu\n", rep->param_annotations.size());
  printf("\n");
}

static void PrintFileStats(const dexx::ReaderMock& rdr) {
  auto h = rdr.Header();
  auto m = rdr.MapList();
  printf("\n.dex file statistics:\n");
  printf("  file_size                     : %u\n", h->file_size);
  printf("  data_size                     : %u\n", h->data_size);
  printf("  link_size                     : %u\n", h->link_size);
  printf("  class_defs_size               : %u\n", h->class_defs_size);
  printf("  string_ids_size               : %u\n", h->string_ids_size);
  printf("  type_ids_size                 : %u\n", h->type_ids_size);
  printf("  proto_ids_size                : %u\n", h->proto_ids_size);
  printf("  field_ids_size                : %u\n", h->field_ids_size);
  printf("  method_ids_size               : %u\n", h->method_ids_size);
  printf("  method_handle_ids_size        : %zu\n", rdr.MethodHandles().size());
  printf("  map_list_size                 : %u\n", m->size);
  printf("\n");
}

static void ListClassDefs(const dexx::ReaderMock& rdr) {
  printf("\nClass definitions:\n");
  auto classes = rdr.ClassDefs();
  auto types = rdr.TypeIds();
  for (dexx::u4 i = 0; i < classes.size(); ++i) {
    auto tid = types[classes[i].class_idx % types.size()];
    const char* desc = rdr.GetStringDescriptor(tid.descriptor_idx);
    printf("  %s\n", desc);
  }
  printf("\n");
}

bool DexterTool::BuildNewImage(std::shared_ptr<irx::DexRepresentation> rep) {
  (void)rep;
  t_writer_ += 0.9;
  printf("[writer] Mock CreateImage (no-op)\n");
  if (out_file_name_) {
    printf("[writer] Would output to: %s\n", out_file_name_);
  }
  return true;
}

int DexterTool::ProcessPath() {
  if (verbose_) printf("\nOpening: %s\n", dex_path_);

  struct stat st;
  if (stat(dex_path_, &st) != 0) {
    printf("ERROR: stat failed for %s : %s\n", dex_path_, strerror(errno));
    return 1;
  }
  if (!S_ISREG(st.st_mode)) {
    printf("ERROR: Not a regular file: %s\n", dex_path_);
    return 1;
  }

  FILE* f = fopen(dex_path_, "rb");
  if (!f) {
    printf("ERROR: can't open %s\n", dex_path_);
    return 1;
  }
  fseek(f, 0, SEEK_END);
  size_t size = (size_t)ftell(f);
  fseek(f, 0, SEEK_SET);
  std::unique_ptr<dexx::u1[]> buf(new dexx::u1[size]);
  if (fread(buf.get(), 1, size, f) != size) {
    printf("ERROR: read failed\n");
    fclose(f);
    return 1;
  }
  fclose(f);

  dexx::ReaderMock rdr(buf.get(), size);

  if (show_map_) PrintMapMock(rdr);
  if (list_classes_) ListClassDefs(rdr);

  // simulate parse time
  t_reader_ += 3.14;
  if (extract_class_name_) {
    std::string desc = ToDescriptor(extract_class_name_);
    printf("[reader] extract %s (mock)\n", desc.c_str());
  } else {
    rdr.CreateFullRepresentation();
  }

  // build mock IR
  auto rep = std::make_shared<irx::DexRepresentation>();
  size_t base = std::max<size_t>(1, size % 17);
  for (size_t i = 0; i < base * 4; ++i) rep->strings.push_back("s");
  for (size_t i = 0; i < base; ++i) rep->types.push_back("t");
  for (size_t i = 0; i < base/1 + 1; ++i) rep->protos.push_back("p");
  for (size_t i = 0; i < base*2; ++i) rep->fields.push_back("f");
  for (size_t i = 0; i < base; ++i) rep->encoded_fields.push_back("ef");
  for (size_t i = 0; i < base*3; ++i) rep->methods.push_back("m");
  for (size_t i = 0; i < base; ++i) rep->encoded_methods.push_back("em");
  for (size_t i = 0; i < base/2 + 1; ++i) rep->classes.push_back("c");
  for (size_t i = 0; i < base; ++i) rep->method_handles.push_back("mh");
  for (size_t i = 0; i < base/2; ++i) rep->type_lists.push_back("tl");
  for (size_t i = 0; i < base*2; ++i) rep->code.push_back("code");
  for (size_t i = 0; i < base; ++i) rep->debug_info.push_back("d");
  for (size_t i = 0; i < base; ++i) rep->encoded_values.push_back("ev");
  for (size_t i = 0; i < base/2; ++i) rep->encoded_arrays.push_back("ea");
  for (size_t i = 0; i < base/3; ++i) rep->annotations.push_back("a");
  for (size_t i = 0; i < base; ++i) rep->annotation_elements.push_back("ae");
  for (size_t i = 0; i < base/2; ++i) rep->annotation_sets.push_back("as");
  for (size_t i = 0; i < base/2; ++i) rep->annotation_set_ref_lists.push_back("arl");
  for (size_t i = 0; i < base/2; ++i) rep->annotations_directories.push_back("ad");
  for (size_t i = 0; i < base/2; ++i) rep->field_annotations.push_back("fa");
  for (size_t i = 0; i < base/2; ++i) rep->method_annotations.push_back("ma");
  for (size_t i = 0; i < base/2; ++i) rep->param_annotations.push_back("pa");

  for (auto &e : exps_) {
    t_exps_ += 0.7;
    if (verbose_) printf("[exp] %s\n", e.c_str());
    experiments_mock::RunExp(e, rep);
  }

  if (disasm_) {
    DisasmMock d(rep, cfg_mode_);
    d.DumpAll();
  }

  if (!BuildNewImage(rep)) return 1;

  if (print_stats_) {
    PrintFileStats(rdr);
    PrintIrStats(rep);
  }

  if (verbose_) {
    printf("\nDone (reader: %.3fms, writer: %.3fms, exps: %.3fms)\n", t_reader_, t_writer_, t_exps_);
  }

  return 0;
}

// -----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DexterTool tool(argc, argv);
  return tool.Run();
}
