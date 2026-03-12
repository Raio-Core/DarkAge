#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
DA Documentation Generator

This script parses Unreal Engine 5 C++ header files and generates comprehensive
markdown documentation for the DA project.

Usage:
    python scripts/generate_docs.py

Features:
    - Parses UCLASS, USTRUCT, UPROPERTY, UFUNCTION macros
    - Generates class hierarchy diagrams
    - Counts statistics (files, classes, lines of code)
    - Updates README.md between auto-update markers
"""

import os
import re
import sys
import io
from pathlib import Path
from dataclasses import dataclass, field
from typing import List, Dict, Optional, Tuple
from datetime import datetime

# Fix Windows console encoding
if sys.platform == 'win32':
    sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')
    sys.stderr = io.TextIOWrapper(sys.stderr.buffer, encoding='utf-8')


@dataclass
class UProperty:
    """Represents a UPROPERTY declaration."""
    name: str
    type: str
    specifiers: List[str]
    category: Optional[str] = None
    comment: Optional[str] = None
    
    def to_markdown(self) -> str:
        spec = " | ".join(self.specifiers) if self.specifiers else "-"
        cat = f"`{self.category}`" if self.category else "-"
        comment = f"<br>_{self.comment}_" if self.comment else ""
        return f"| `{self.name}` | `{self.type}` | {spec} | {cat} |{comment}"


@dataclass
class UFunction:
    """Represents a UFUNCTION declaration."""
    name: str
    return_type: str
    parameters: str
    specifiers: List[str]
    comment: Optional[str] = None
    
    def to_markdown(self) -> str:
        spec = " | ".join(self.specifiers) if self.specifiers else "-"
        params = f"`{self.parameters}`" if self.parameters else "-"
        comment = f"<br>_{self.comment}_" if self.comment else ""
        return f"| `{self.name}` | `{self.return_type}` | {params} | {spec} |{comment}"


@dataclass
class UClass:
    """Represents a parsed UCLASS."""
    name: str
    parent_classes: List[str]
    module: str
    file_path: str
    specifiers: List[str]
    properties: List[UProperty] = field(default_factory=list)
    functions: List[UFunction] = field(default_factory=list)
    comment: Optional[str] = None
    
    def full_inheritance(self) -> str:
        if self.parent_classes:
            return " -> ".join(self.parent_classes + [self.name])
        return self.name


@dataclass
class UStruct:
    """Represents a parsed USTRUCT."""
    name: str
    file_path: str
    specifiers: List[str]
    properties: List[UProperty] = field(default_factory=list)
    comment: Optional[str] = None


class UnrealHeaderParser:
    """Parser for Unreal Engine C++ header files."""
    
    UPROPERTY_PATTERN = re.compile(
        r'UPROPERTY\s*\(\s*([^)]*)\s*\)\s*\n?\s*'
        r'([^;{]+?)([A-Za-z_][A-Za-z0-9_]*)\s*;',
        re.MULTILINE
    )
    
    UFUNCTION_PATTERN = re.compile(
        r'UFUNCTION\s*\(\s*([^)]*)\s*\)\s*\n?\s*'
        r'((?:virtual\s+)?(?:static\s+)?(?:const\s+)?(?:unsigned\s+)?[\w\s:<>,*&]+?)\s+'
        r'([A-Za-z_][A-Za-z0-9_]*)\s*\(([^)]*)\)\s*(?:const\s*)?(?:override\s*)?;',
        re.MULTILINE
    )
    
    UCLASS_PATTERN = re.compile(
        r'UCLASS\s*\(\s*([^)]*)\s*\)\s*\n?\s*'
        r'class\s+(?:[A-Z_]+_API\s+)?([A-Za-z_][A-Za-z0-9_]*)'
        r'(?:\s*:\s*public\s+([^{]+))?',
        re.MULTILINE
    )
    
    USTRUCT_PATTERN = re.compile(
        r'USTRUCT\s*\(\s*([^)]*)\s*\)\s*\n?\s*'
        r'struct\s+(?:[A-Z_]+_API\s+)?([A-Za-z_][A-Za-z0-9_]*)',
        re.MULTILINE
    )
    
    COMMENT_PATTERN = re.compile(
        r'/\*\*(.*?)\*/',
        re.DOTALL
    )
    
    def __init__(self, root_dir: str):
        self.root_dir = Path(root_dir)
        self.classes: List[UClass] = []
        self.structs: List[UStruct] = []
        self.header_files: List[Path] = []
        
    def find_header_files(self) -> List[Path]:
        """Find all .h files in the Source directory."""
        source_dir = self.root_dir / "Source" / "DA"
        if not source_dir.exists():
            return []
        
        self.header_files = list(source_dir.rglob("*.h"))
        return self.header_files
    
    def extract_comment(self, content: str, position: int) -> Optional[str]:
        """Extract comment before a given position."""
        before = content[:position]
        matches = list(self.COMMENT_PATTERN.finditer(before))
        if matches:
            last_match = matches[-1]
            comment = last_match.group(1).strip()
            lines = [line.strip().lstrip('*').strip() for line in comment.split('\n')]
            return ' '.join(line for line in lines if line)
        return None
    
    def parse_specifiers(self, spec_str: str) -> Tuple[List[str], Optional[str]]:
        """Parse UPROPERTY/UFUNCTION specifiers and extract category."""
        specifiers = []
        category = None
        
        cat_match = re.search(r'Category\s*=\s*"([^"]*)"', spec_str)
        if cat_match:
            category = cat_match.group(1)
        
        parts = [p.strip() for p in spec_str.split(',')]
        for part in parts:
            part = part.strip()
            if part and not part.startswith('Category'):
                spec_name = part.split('=')[0].strip()
                if spec_name:
                    specifiers.append(spec_name)
        
        return specifiers, category
    
    def parse_type_and_name(self, decl: str) -> Tuple[str, str]:
        """Parse type and variable name from declaration."""
        decl = decl.strip()
        type_pattern = r'(TObjectPtr<[^>]+>|TSubclassOf<[^>]+>|TArray<[^>]+>|TMap<[^>]+>|TSet<[^>]+>|[\w:]+(?:\s*[*&])?)\s+([A-Za-z_][A-Za-z0-9_]*)\s*$'
        match = re.search(type_pattern, decl)
        
        if match:
            return match.group(1).strip(), match.group(2)
        
        parts = decl.rsplit(None, 1)
        if len(parts) >= 2:
            return parts[0], parts[1]
        
        return decl, "unknown"
    
    def parse_header_file(self, file_path: Path) -> None:
        """Parse a single header file."""
        try:
            content = file_path.read_text(encoding='utf-8')
        except Exception as e:
            print(f"Warning: Could not read {file_path}: {e}")
            return
        
        module = "DA"
        relative_path = file_path.relative_to(self.root_dir)
        
        for match in self.UCLASS_PATTERN.finditer(content):
            spec_str = match.group(1) if match.group(1) else ""
            class_name = match.group(2)
            inheritance = match.group(3)
            
            specifiers, _ = self.parse_specifiers(spec_str)
            
            parent_classes = []
            if inheritance:
                parents = [p.strip() for p in inheritance.split(',')]
                for parent in parents:
                    parent_name = parent.split()[-1].strip()
                    if parent_name and parent_name != class_name:
                        parent_classes.append(parent_name)
            
            comment = self.extract_comment(content, match.start())
            
            uclass = UClass(
                name=class_name,
                parent_classes=parent_classes,
                module=module,
                file_path=str(relative_path),
                specifiers=specifiers,
                comment=comment
            )
            self.classes.append(uclass)
            self._parse_class_members(content, match.end(), uclass)
        
        for match in self.USTRUCT_PATTERN.finditer(content):
            spec_str = match.group(1) if match.group(1) else ""
            struct_name = match.group(2)
            
            specifiers, _ = self.parse_specifiers(spec_str)
            comment = self.extract_comment(content, match.start())
            
            ustruct = UStruct(
                name=struct_name,
                file_path=str(relative_path),
                specifiers=specifiers,
                comment=comment
            )
            self.structs.append(ustruct)
    
    def _parse_class_members(self, content: str, start_pos: int, uclass: UClass) -> None:
        """Parse properties and functions within a class."""
        class_start = content.find('{', start_pos)
        if class_start == -1:
            return
        
        brace_count = 1
        class_end = class_start + 1
        for i, char in enumerate(content[class_start + 1:], class_start + 1):
            if char == '{':
                brace_count += 1
            elif char == '}':
                brace_count -= 1
                if brace_count == 0:
                    class_end = i
                    break
        
        class_body = content[class_start:class_end]
        
        for match in self.UPROPERTY_PATTERN.finditer(class_body):
            spec_str = match.group(1) if match.group(1) else ""
            decl = match.group(2).strip() if match.group(2) else ""
            
            specifiers, category = self.parse_specifiers(spec_str)
            var_type, var_name = self.parse_type_and_name(decl)
            
            comment = self.extract_comment(class_body, match.start())
            
            prop = UProperty(
                name=var_name,
                type=var_type,
                specifiers=specifiers,
                category=category,
                comment=comment
            )
            uclass.properties.append(prop)
        
        for match in self.UFUNCTION_PATTERN.finditer(class_body):
            spec_str = match.group(1) if match.group(1) else ""
            return_type = match.group(2).strip() if match.group(2) else "void"
            func_name = match.group(3)
            params = match.group(4).strip() if match.group(4) else ""
            
            specifiers, _ = self.parse_specifiers(spec_str)
            comment = self.extract_comment(class_body, match.start())
            
            func = UFunction(
                name=func_name,
                return_type=return_type,
                parameters=params,
                specifiers=specifiers,
                comment=comment
            )
            uclass.functions.append(func)
    
    def parse_all(self) -> None:
        """Parse all header files."""
        self.find_header_files()
        for header_file in self.header_files:
            self.parse_header_file(header_file)
    
    def get_statistics(self) -> Dict:
        """Generate statistics about the codebase."""
        total_lines = 0
        cpp_files = list(self.root_dir.rglob("Source/**/*.cpp"))
        
        for file in self.header_files + cpp_files:
            try:
                with open(file, 'r', encoding='utf-8', errors='ignore') as f:
                    total_lines += len(f.readlines())
            except:
                pass
        
        return {
            "header_files": len(self.header_files),
            "cpp_files": len(cpp_files),
            "total_classes": len(self.classes),
            "total_structs": len(self.structs),
            "total_lines": total_lines
        }


class DocumentationGenerator:
    """Generates markdown documentation from parsed Unreal Engine classes."""
    
    def __init__(self, parser: UnrealHeaderParser, root_dir: str):
        self.parser = parser
        self.root_dir = Path(root_dir)
        self.docs_dir = self.root_dir / "docs"
        self.docs_dir.mkdir(exist_ok=True)
    
    def generate_class_hierarchy_mermaid(self) -> str:
        """Generate a Mermaid class diagram."""
        lines = ["```mermaid", "classDiagram"]
        
        for uclass in self.parser.classes:
            for parent in uclass.parent_classes:
                clean_parent = parent.split('<')[0].strip()
                lines.append(f"    {clean_parent} <|-- {uclass.name}")
        
        for uclass in self.parser.classes:
            lines.append(f"    class {uclass.name} {{")
            
            for prop in uclass.properties[:5]:
                visibility = "+" if "BlueprintReadOnly" in prop.specifiers or "BlueprintReadWrite" in prop.specifiers else "-"
                lines.append(f"        {visibility}{prop.name}: {prop.type}")
            
            for func in uclass.functions[:5]:
                visibility = "+" if "BlueprintCallable" in func.specifiers or "BlueprintPure" in func.specifiers else "-"
                params = "()" if not func.parameters else "(...)"
                lines.append(f"        {visibility}{func.name}{params}")
            
            lines.append("    }")
        
        lines.append("```")
        return "\n".join(lines)
    
    def generate_class_documentation(self, uclass: UClass) -> str:
        """Generate markdown documentation for a single class."""
        lines = []
        
        lines.append(f"# {uclass.name}")
        lines.append("")
        
        if uclass.comment:
            lines.append(f"*{uclass.comment}*")
            lines.append("")
        
        lines.append(f"**File:** `{uclass.file_path}`")
        lines.append("")
        
        if uclass.parent_classes:
            lines.append("## Inheritance")
            lines.append("")
            lines.append(f"```\n{uclass.full_inheritance()}\n```")
            lines.append("")
        
        if uclass.specifiers:
            lines.append("## Specifiers")
            lines.append("")
            lines.append(" | ".join([f"`{s}`" for s in uclass.specifiers]))
            lines.append("")
        
        if uclass.properties:
            lines.append("## Properties")
            lines.append("")
            lines.append("| Name | Type | Specifiers | Category |")
            lines.append("|------|------|------------|----------|")
            for prop in uclass.properties:
                lines.append(prop.to_markdown())
            lines.append("")
        
        if uclass.functions:
            lines.append("## Functions")
            lines.append("")
            lines.append("| Name | Return Type | Parameters | Specifiers |")
            lines.append("|------|-------------|------------|------------|")
            for func in uclass.functions:
                lines.append(func.to_markdown())
            lines.append("")
        
        return "\n".join(lines)
    
    def generate_struct_documentation(self, ustruct: UStruct) -> str:
        """Generate markdown documentation for a struct."""
        lines = []
        
        lines.append(f"# {ustruct.name}")
        lines.append("")
        
        if ustruct.comment:
            lines.append(f"*{ustruct.comment}*")
            lines.append("")
        
        lines.append(f"**File:** `{ustruct.file_path}`")
        lines.append("")
        
        if ustruct.specifiers:
            lines.append("## Specifiers")
            lines.append("")
            lines.append(" | ".join([f"`{s}`" for s in ustruct.specifiers]))
            lines.append("")
        
        if ustruct.properties:
            lines.append("## Properties")
            lines.append("")
            lines.append("| Name | Type | Specifiers | Category |")
            lines.append("|------|------|------------|----------|")
            for prop in ustruct.properties:
                lines.append(prop.to_markdown())
            lines.append("")
        
        return "\n".join(lines)
    
    def generate_api_index(self) -> str:
        """Generate an index of all classes and structs."""
        lines = ["# API Reference", ""]
        
        if self.parser.classes:
            lines.append("## Classes")
            lines.append("")
            lines.append("| Class | Inheritance | File |")
            lines.append("|-------|-------------|------|")
            
            for uclass in sorted(self.parser.classes, key=lambda c: c.name):
                inheritance = " -> ".join(uclass.parent_classes[-1:]) if uclass.parent_classes else "-"
                lines.append(f"| [{uclass.name}](Classes/{uclass.name}.md) | {inheritance} | `{uclass.file_path}` |")
            lines.append("")
        
        if self.parser.structs:
            lines.append("## Structs")
            lines.append("")
            lines.append("| Struct | File |")
            lines.append("|--------|------|")
            
            for ustruct in sorted(self.parser.structs, key=lambda s: s.name):
                lines.append(f"| [{ustruct.name}](Structs/{ustruct.name}.md) | `{ustruct.file_path}` |")
            lines.append("")
        
        return "\n".join(lines)
    
    def generate_architecture_overview(self) -> str:
        """Generate an architecture overview document."""
        lines = [
            "# Architecture Overview",
            "",
            "This document provides a high-level overview of the DA project's architecture.",
            "",
            "## System Architecture",
            "",
            self.generate_class_hierarchy_mermaid(),
            "",
            "## Core Systems",
            "",
        ]
        
        systems = {}
        for uclass in self.parser.classes:
            parts = uclass.file_path.split('/')
            if 'Systems' in parts:
                idx = parts.index('Systems')
                if idx + 1 < len(parts):
                    system = parts[idx + 1]
                    if system not in systems:
                        systems[system] = []
                    systems[system].append(uclass)
            elif 'Game' in parts:
                idx = parts.index('Game')
                if idx + 1 < len(parts):
                    system = f"Game/{parts[idx + 1]}"
                    if system not in systems:
                        systems[system] = []
                    systems[system].append(uclass)
            elif 'UI' in parts:
                if 'UI' not in systems:
                    systems['UI'] = []
                systems['UI'].append(uclass)
            elif 'Input' in parts:
                if 'Input' not in systems:
                    systems['Input'] = []
                systems['Input'].append(uclass)
        
        for system, classes in sorted(systems.items()):
            lines.append(f"### {system}")
            lines.append("")
            for uclass in sorted(classes, key=lambda c: c.name):
                desc = uclass.comment if uclass.comment else f"{uclass.name} class"
                lines.append(f"- **[{uclass.name}](Classes/{uclass.name}.md)** - {desc}")
            lines.append("")
        
        return "\n".join(lines)
    
    def generate_all_documentation(self) -> None:
        """Generate all documentation files."""
        classes_dir = self.docs_dir / "API" / "Classes"
        structs_dir = self.docs_dir / "API" / "Structs"
        classes_dir.mkdir(parents=True, exist_ok=True)
        structs_dir.mkdir(parents=True, exist_ok=True)
        
        for uclass in self.parser.classes:
            doc = self.generate_class_documentation(uclass)
            (classes_dir / f"{uclass.name}.md").write_text(doc, encoding='utf-8')
        
        for ustruct in self.parser.structs:
            doc = self.generate_struct_documentation(ustruct)
            (structs_dir / f"{ustruct.name}.md").write_text(doc, encoding='utf-8')
        
        api_index = self.generate_api_index()
        (self.docs_dir / "API" / "README.md").write_text(api_index, encoding='utf-8')
        
        arch_doc = self.generate_architecture_overview()
        (self.docs_dir / "Architecture.md").write_text(arch_doc, encoding='utf-8')
        
        print(f"Generated documentation for {len(self.parser.classes)} classes and {len(self.parser.structs)} structs")


def update_readme(root_dir: Path, stats: Dict, parser: UnrealHeaderParser) -> None:
    """Update README.md with auto-generated statistics and diagrams."""
    readme_path = root_dir / "README.md"
    
    if not readme_path.exists():
        print("README.md not found, skipping update")
        return
    
    content = readme_path.read_text(encoding='utf-8')
    
    stats_section = f"""<!-- STATS_START -->
## Project Statistics

| Metric | Count |
|--------|-------|
| **Header Files** | {stats['header_files']} |
| **Source Files** | {stats['cpp_files']} |
| **Total Classes** | {stats['total_classes']} |
| **Total Structs** | {stats['total_structs']} |
| **Lines of Code** | {stats['total_lines']:,} |

<!-- STATS_END -->"""
    
    stats_pattern = r'<!-- STATS_START -->.*?<!-- STATS_END -->'
    if re.search(stats_pattern, content, re.DOTALL):
        content = re.sub(stats_pattern, stats_section, content, flags=re.DOTALL)
    
    if parser.classes:
        class_list = "<!-- CLASSES_START -->\n## C++ Classes\n\n"
        class_list += "| Class | Description | File |\n|-------|-------------|------|\n"
        
        for uclass in sorted(parser.classes, key=lambda c: c.name)[:20]:
            desc = (uclass.comment[:50] + "...") if uclass.comment and len(uclass.comment) > 50 else (uclass.comment or "-")
            class_list += f"| **{uclass.name}** | {desc} | `{Path(uclass.file_path).name}` |\n"
        
        class_list += "\n*See [API Documentation](docs/API/README.md) for complete reference*\n<!-- CLASSES_END -->"
        
        class_pattern = r'<!-- CLASSES_START -->.*?<!-- CLASSES_END -->'
        if re.search(class_pattern, content, re.DOTALL):
            content = re.sub(class_pattern, class_list, content, flags=re.DOTALL)
    
    readme_path.write_text(content, encoding='utf-8')
    print("Updated README.md with auto-generated content")


def main():
    """Main entry point."""
    script_dir = Path(__file__).parent.resolve()
    root_dir = script_dir.parent
    
    print("=" * 60)
    print("DA Documentation Generator")
    print("=" * 60)
    
    print("\n[1/4] Parsing header files...")
    parser = UnrealHeaderParser(str(root_dir))
    parser.parse_all()
    
    print(f"   Found {len(parser.header_files)} header files")
    print(f"   Parsed {len(parser.classes)} classes")
    print(f"   Parsed {len(parser.structs)} structs")
    
    print("\n[2/4] Generating documentation...")
    generator = DocumentationGenerator(parser, str(root_dir))
    generator.generate_all_documentation()
    
    stats = parser.get_statistics()
    print(f"\n[3/4] Statistics:")
    print(f"   Header Files: {stats['header_files']}")
    print(f"   Source Files: {stats['cpp_files']}")
    print(f"   Total Classes: {stats['total_classes']}")
    print(f"   Total Structs: {stats['total_structs']}")
    print(f"   Lines of Code: {stats['total_lines']:,}")
    
    print("\n[4/4] Updating README.md...")
    update_readme(root_dir, stats, parser)
    
    print("\n" + "=" * 60)
    print("Documentation generation complete!")
    print(f"Generated files in: {root_dir / 'docs'}")
    print("=" * 60)


if __name__ == "__main__":
    main()
