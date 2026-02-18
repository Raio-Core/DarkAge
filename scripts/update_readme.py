#!/usr/bin/env python3
"""
Auto-updating README generator for DA (Unreal Engine Project)
This script parses project files and generates dynamic README content.
Features automatic semantic versioning based on commit history.
Features automatic copyright management and header updates.
"""

import os
import re
import json
import subprocess
from pathlib import Path
from datetime import datetime, timezone
from typing import Dict, List, Tuple, Optional


class CopyrightManager:
    """Manages copyright headers and notices for the project."""
    
    def __init__(self, project_root: Path):
        self.project_root = project_root
        self.copyright_file = project_root / "COPYRIGHT"
        self.source_dir = project_root / "Source"
        self.current_year = datetime.now().year
    
    def get_copyright_holders(self) -> List[str]:
        """Get list of copyright holders from COPYRIGHT file."""
        if self.copyright_file.exists():
            try:
                with open(self.copyright_file, 'r', encoding='utf-8') as f:
                    holders = [line.strip() for line in f.readlines() if line.strip()]
                    return holders
            except Exception:
                pass
        return ["RaioCore", "Raioix"]  # Default holders
    
    def get_copyright_string(self) -> str:
        """Get formatted copyright string."""
        holders = self.get_copyright_holders()
        if len(holders) == 1:
            return f"Copyright {self.current_year} {holders[0]}. All Rights Reserved."
        elif len(holders) == 2:
            return f"Copyright {self.current_year} {holders[0]} and {holders[1]}. All Rights Reserved."
        else:
            return f"Copyright {self.current_year} {', '.join(holders[:-1])}, and {holders[-1]}. All Rights Reserved."
    
    def get_short_copyright(self) -> str:
        """Get short copyright string for file headers."""
        holders = self.get_copyright_holders()
        if len(holders) == 1:
            return f"Copyright {self.current_year} {holders[0]}"
        else:
            return f"Copyright {self.current_year} {holders[0]} et al."
    
    def generate_header(self) -> str:
        """Generate the standard copyright header for source files."""
        return f"// {self.get_copyright_string()}\n"
    
    def scan_file_copyrights(self) -> Dict[str, List[str]]:
        """Scan all source files and extract copyright information."""
        copyright_info = {}
        
        for source_file in self.source_dir.rglob("*.h"):
            try:
                with open(source_file, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                    
                # Extract copyright from first 5 lines
                first_lines = content.split('\n')[:5]
                copyright_line = None
                
                for line in first_lines:
                    if 'copyright' in line.lower():
                        copyright_line = line.strip().lstrip('/').strip()
                        break
                
                relative_path = str(source_file.relative_to(self.project_root))
                if copyright_line:
                    if copyright_line not in copyright_info:
                        copyright_info[copyright_line] = []
                    copyright_info[copyright_line].append(relative_path)
                    
            except Exception:
                pass
        
        return copyright_info
    
    def update_source_file_headers(self) -> int:
        """Update all source files with correct copyright headers."""
        updated_count = 0
        new_header = self.generate_header()
        holders = self.get_copyright_holders()
        
        for source_file in list(self.source_dir.rglob("*.h")) + list(self.source_dir.rglob("*.cpp")):
            try:
                with open(source_file, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                
                lines = content.split('\n')
                
                # Check if first line is a copyright notice
                if lines and ('copyright' in lines[0].lower() or 'epic games' in lines[0].lower()):
                    old_header = lines[0]
                    
                    # Check if it needs updating
                    needs_update = False
                    
                    # Check if it's Epic Games copyright (needs replacement)
                    if 'epic games' in old_header.lower():
                        needs_update = True
                    # Check if year is current
                    elif str(self.current_year) not in old_header:
                        needs_update = True
                    # Check if copyright holders are correct
                    elif not any(holder.lower() in old_header.lower() for holder in holders):
                        needs_update = True
                    
                    if needs_update:
                        lines[0] = new_header.strip()
                        new_content = '\n'.join(lines)
                        
                        with open(source_file, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                        updated_count += 1
                else:
                    # No copyright header, add one
                    lines.insert(0, new_header.strip())
                    lines.insert(1, '')  # Empty line after copyright
                    new_content = '\n'.join(lines)
                    
                    with open(source_file, 'w', encoding='utf-8') as f:
                        f.write(new_content)
                    updated_count += 1
                    
            except Exception as e:
                print(f"Error updating {source_file}: {e}")
        
        return updated_count
    
    def get_copyright_summary(self) -> Dict:
        """Get a summary of copyright status in the project."""
        copyright_info = self.scan_file_copyrights()
        holders = self.get_copyright_holders()
        
        total_files = len(list(self.source_dir.rglob("*.h"))) + len(list(self.source_dir.rglob("*.cpp")))
        
        correct_copyright = self.get_copyright_string()
        files_with_correct = 0
        files_with_epic = 0
        files_with_placeholder = 0
        files_without = 0
        
        for source_file in list(self.source_dir.rglob("*.h")) + list(self.source_dir.rglob("*.cpp")):
            try:
                with open(source_file, 'r', encoding='utf-8', errors='ignore') as f:
                    first_line = f.readline().lower()
                
                if 'epic games' in first_line:
                    files_with_epic += 1
                elif 'fill out your copyright' in first_line:
                    files_with_placeholder += 1
                elif any(holder.lower() in first_line for holder in holders):
                    files_with_correct += 1
                else:
                    files_without += 1
            except Exception:
                files_without += 1
        
        return {
            "total_files": total_files,
            "files_with_correct_copyright": files_with_correct,
            "files_with_epic_copyright": files_with_epic,
            "files_with_placeholder": files_with_placeholder,
            "files_without_copyright": files_without,
            "copyright_holders": holders,
            "copyright_string": correct_copyright
        }


class VersionManager:
    """Manages semantic versioning with automatic increment based on commits."""
    
    # Development stages in order
    STAGES = ["pre-alpha", "alpha", "beta", "rc", "stable"]
    
    # Commit type to version bump mapping
    VERSION_BUMPS = {
        "breaking": "major",  # BREAKING CHANGE or ! in type
        "feat": "minor",      # New feature
        "feature": "minor",   # New feature (alternate)
        "fix": "patch",       # Bug fix
        "perf": "patch",      # Performance improvement
        "refactor": "patch",  # Code refactoring
        "docs": "none",       # Documentation only
        "style": "none",      # Code style changes
        "test": "none",       # Adding tests
        "chore": "none",      # Maintenance tasks
        "ci": "none",         # CI changes
        "build": "none",      # Build system changes
    }
    
    def __init__(self, project_root: Path):
        self.project_root = project_root
        self.version_file = project_root / "VERSION"
        self.stage_file = project_root / "STAGE"
        self.build_file = project_root / "BUILD"
    
    def get_current_version(self) -> Tuple[int, int, int]:
        """Get current version from VERSION file."""
        if self.version_file.exists():
            try:
                with open(self.version_file, 'r', encoding='utf-8') as f:
                    version_str = f.read().strip()
                    parts = version_str.split('.')
                    if len(parts) >= 3:
                        return (int(parts[0]), int(parts[1]), int(parts[2]))
            except Exception:
                pass
        return (0, 1, 0)  # Default starting version
    
    def get_current_stage(self) -> str:
        """Get current development stage."""
        if self.stage_file.exists():
            try:
                with open(self.stage_file, 'r', encoding='utf-8') as f:
                    stage = f.read().strip().lower()
                    if stage in self.STAGES:
                        return stage
            except Exception:
                pass
        return "pre-alpha"  # Default stage
    
    def get_build_number(self) -> int:
        """Get current build number (incremented on every commit)."""
        if self.build_file.exists():
            try:
                with open(self.build_file, 'r', encoding='utf-8') as f:
                    return int(f.read().strip())
            except Exception:
                pass
        return 1
    
    def parse_commit_message(self, message: str) -> Dict[str, str]:
        """Parse conventional commit message."""
        # Pattern: type(scope): description
        pattern = r'^(\w+)(?:\(([^)]+)\))?(!)?:\s*(.+)$'
        match = re.match(pattern, message, re.MULTILINE)
        
        if match:
            commit_type = match.group(1).lower()
            scope = match.group(2) or ""
            breaking = match.group(3) == "!" or "BREAKING CHANGE" in message.upper()
            description = match.group(4)
            
            return {
                "type": commit_type,
                "scope": scope,
                "breaking": breaking,
                "description": description
            }
        
        # Non-conventional commit - treat as patch
        return {
            "type": "other",
            "scope": "",
            "breaking": False,
            "description": message.split('\n')[0]
        }
    
    def analyze_commits_for_version(self, commits: List[Dict]) -> Dict:
        """Analyze commits to determine version changes."""
        current_version = self.get_current_version()
        current_stage = self.get_current_stage()
        current_build = self.get_build_number()
        
        bump_type = "none"
        breaking_changes = 0
        new_features = 0
        bug_fixes = 0
        other_changes = 0
        
        for commit in commits:
            parsed = self.parse_commit_message(commit.get("message", ""))
            commit_type = parsed["type"]
            
            if parsed["breaking"]:
                breaking_changes += 1
                bump_type = "major"
            elif commit_type in ["feat", "feature"]:
                new_features += 1
                if bump_type != "major":
                    bump_type = "minor"
            elif commit_type == "fix":
                bug_fixes += 1
                if bump_type not in ["major", "minor"]:
                    bump_type = "patch"
            elif commit_type in self.VERSION_BUMPS:
                if self.VERSION_BUMPS[commit_type] == "patch" and bump_type == "none":
                    bump_type = "patch"
                other_changes += 1
            else:
                other_changes += 1
        
        # Calculate new version
        major, minor, patch = current_version
        new_build = current_build + len(commits)
        
        if bump_type == "major":
            major += 1
            minor = 0
            patch = 0
        elif bump_type == "minor":
            minor += 1
            patch = 0
        elif bump_type == "patch":
            patch += 1
        
        # Determine stage progression based on version and features
        new_stage = current_stage
        if major >= 1 and new_stage in ["pre-alpha", "alpha"]:
            new_stage = "beta"
        elif new_features >= 10 and new_stage == "pre-alpha":
            new_stage = "alpha"
        elif new_features >= 20 and bug_fixes >= 5 and new_stage == "alpha":
            new_stage = "beta"
        elif major >= 1 and minor >= 0 and new_stage == "beta":
            new_stage = "rc"
        elif major >= 1 and minor >= 1 and new_stage == "rc":
            new_stage = "stable"
        
        return {
            "version": (major, minor, patch),
            "version_string": f"{major}.{minor}.{patch}",
            "stage": new_stage,
            "build": new_build,
            "bump_type": bump_type,
            "stats": {
                "breaking_changes": breaking_changes,
                "new_features": new_features,
                "bug_fixes": bug_fixes,
                "other_changes": other_changes
            }
        }
    
    def update_version_files(self, version_info: Dict) -> None:
        """Update VERSION, STAGE, and BUILD files."""
        # Update VERSION
        with open(self.version_file, 'w', encoding='utf-8') as f:
            f.write(version_info["version_string"])
        
        # Update STAGE
        with open(self.stage_file, 'w', encoding='utf-8') as f:
            f.write(version_info["stage"])
        
        # Update BUILD
        with open(self.build_file, 'w', encoding='utf-8') as f:
            f.write(str(version_info["build"]))
    
    def get_version_info(self, commits: List[Dict]) -> Dict:
        """Get complete version information."""
        version_info = self.analyze_commits_for_version(commits)
        
        # Only update files if there are actual commits to analyze
        if commits:
            self.update_version_files(version_info)
        
        return {
            **version_info,
            "full_version": f"v{version_info['version_string']}-{version_info['stage']}+build.{version_info['build']}",
            "display_version": f"{version_info['version_string']}-{version_info['stage']}"
        }


class ProjectStats:
    """Gathers statistics about the project."""
    
    def __init__(self, project_root: Path):
        self.project_root = project_root
        self.source_dir = project_root / "Source"
        self.config_dir = project_root / "Config"
    
    def get_uproject_info(self) -> Dict:
        """Parse the .uproject file for project information."""
        uproject_files = list(self.project_root.glob("*.uproject"))
        if not uproject_files:
            return {"name": "DA", "version": "0.1.0", "engine": "5.7"}
        
        uproject_path = uproject_files[0]
        try:
            with open(uproject_path, 'r', encoding='utf-8') as f:
                data = json.load(f)
            
            return {
                "name": uproject_path.stem,
                "version": data.get("ProjectVersion", "0.1.0"),
                "engine": data.get("EngineAssociation", "5.3"),
                "description": data.get("Description", ""),
                "modules": len(data.get("Modules", []))
            }
        except Exception:
            return {"name": uproject_path.stem, "version": "0.1.0", "engine": "5.3"}
    
    def count_cpp_files(self) -> Dict[str, int]:
        """Count C++ source and header files."""
        headers = list(self.source_dir.rglob("*.h"))
        sources = list(self.source_dir.rglob("*.cpp"))
        
        return {
            "headers": len(headers),
            "sources": len(sources),
            "total": len(headers) + len(sources)
        }
    
    def count_lines_of_code(self) -> Dict[str, int]:
        """Count lines of code in C++ files."""
        header_lines = 0
        source_lines = 0
        comment_lines = 0
        
        for header in self.source_dir.rglob("*.h"):
            try:
                with open(header, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                    lines = content.split('\n')
                    header_lines += len(lines)
                    # Count comment lines
                    for line in lines:
                        stripped = line.strip()
                        if stripped.startswith('//') or stripped.startswith('/*') or stripped.startswith('*'):
                            comment_lines += 1
            except Exception:
                pass
        
        for source in self.source_dir.rglob("*.cpp"):
            try:
                with open(source, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                    lines = content.split('\n')
                    source_lines += len(lines)
                    for line in lines:
                        stripped = line.strip()
                        if stripped.startswith('//') or stripped.startswith('/*') or stripped.startswith('*'):
                            comment_lines += 1
            except Exception:
                pass
        
        return {
            "header_lines": header_lines,
            "source_lines": source_lines,
            "total_lines": header_lines + source_lines,
            "comment_lines": comment_lines,
            "code_lines": header_lines + source_lines - comment_lines
        }
    
    def get_class_list(self) -> List[Dict[str, str]]:
        """Extract all C++ classes from header files."""
        classes = []
        seen_classes = set()  # Track seen classes to avoid duplicates
        
        # Pattern to match UCLASS decorated classes with optional API macro
        uclass_pattern = re.compile(
            r'UCLASS\s*\([^)]*\)\s*\n?\s*'
            r'class\s+(?:\w+_API\s+)?(\w+)\s*(?::\s*(?:public|private|protected)\s+(\w+))?',
            re.MULTILINE
        )
        
        # Pattern to match USTRUCT
        ustruct_pattern = re.compile(
            r'USTRUCT\s*\([^)]*\)\s*\n?\s*'
            r'struct\s+(?:\w+_API\s+)?(\w+)',
            re.MULTILINE
        )
        
        # Pattern to match UENUM
        uenum_pattern = re.compile(
            r'UENUM\s*\([^)]*\)\s*\n?\s*'
            r'enum\s+(?:class\s+)?(\w+)',
            re.MULTILINE
        )
        
        for header in self.source_dir.rglob("*.h"):
            try:
                with open(header, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                
                relative_path = header.relative_to(self.project_root)
                
                # Find UCLASS decorated classes
                for match in uclass_pattern.finditer(content):
                    class_name = match.group(1)
                    base_class = match.group(2) if match.lastindex and match.lastindex >= 2 else None
                    
                    # Skip if already seen
                    if class_name in seen_classes:
                        continue
                    seen_classes.add(class_name)
                    
                    # Extract brief description from comments
                    brief = self._extract_brief_description(content, match.start())
                    
                    classes.append({
                        "name": class_name,
                        "type": "Class",
                        "base": base_class,
                        "file": str(relative_path),
                        "brief": brief
                    })
                
                # Find USTRUCT decorated structs
                for match in ustruct_pattern.finditer(content):
                    struct_name = match.group(1)
                    if struct_name in seen_classes:
                        continue
                    seen_classes.add(struct_name)
                    
                    brief = self._extract_brief_description(content, match.start())
                    classes.append({
                        "name": struct_name,
                        "type": "Struct",
                        "base": None,
                        "file": str(relative_path),
                        "brief": brief
                    })
                
                # Find UENUM decorated enums
                for match in uenum_pattern.finditer(content):
                    enum_name = match.group(1)
                    if enum_name in seen_classes:
                        continue
                    seen_classes.add(enum_name)
                    
                    brief = self._extract_brief_description(content, match.start())
                    classes.append({
                        "name": enum_name,
                        "type": "Enum",
                        "base": None,
                        "file": str(relative_path),
                        "brief": brief
                    })
                    
            except Exception:
                pass
        
        # Sort by name
        classes.sort(key=lambda x: x["name"])
        return classes
    
    def _extract_brief_description(self, content: str, position: int) -> str:
        """Extract brief description from comments before a class."""
        # Look for UCLASS or similar macro
        before_content = content[max(0, position-500):position]
        
        # Look for @brief or single-line comment
        brief_match = re.search(r'@brief\s+(.+?)(?:\n|\*/)', before_content, re.DOTALL)
        if brief_match:
            return brief_match.group(1).strip()
        
        # Look for single-line comment just before
        comment_match = re.search(r'//\s*(.+?)\n\s*$', before_content)
        if comment_match:
            return comment_match.group(1).strip()
        
        return ""
    
    def get_directory_structure(self) -> str:
        """Generate a tree structure of the Source directory."""
        structure = []
        
        def walk_dir(path: Path, prefix: str = ""):
            items = sorted(path.iterdir(), key=lambda x: (not x.is_dir(), x.name))
            for i, item in enumerate(items):
                is_last = i == len(items) - 1
                current_prefix = "    " if is_last else "    "
                next_prefix = "    " if is_last else "    "
                
                if item.is_dir():
                    structure.append(f"{prefix}{'    ' if is_last else '    '}{item.name}/")
                    walk_dir(item, prefix + next_prefix)
                else:
                    structure.append(f"{prefix}{'    ' if is_last else '    '}{item.name}")
        
        if self.source_dir.exists():
            structure.append("Source/")
            walk_dir(self.source_dir, "")
        
        return "\n".join(structure)
    
    def get_gameplay_tags(self) -> List[str]:
        """Parse gameplay tags from config."""
        tags = []
        tags_file = self.config_dir / "DefaultGameplayTags.ini"
        
        if tags_file.exists():
            try:
                with open(tags_file, 'r', encoding='utf-8') as f:
                    content = f.read()
                
                # Find all gameplay tags
                tag_matches = re.findall(r'\+GameplayTagList=\(Tag="([^"]+)"', content)
                tags = sorted(set(tag_matches))
            except Exception:
                pass
        
        return tags


class GitInfo:
    """Gathers Git repository information."""
    
    def __init__(self, repo_root: Path):
        self.repo_root = repo_root
    
    def get_recent_commits(self, count: int = 10) -> List[Dict[str, str]]:
        """Get recent commits."""
        try:
            result = subprocess.run(
                ["git", "log", f"-{count}", "--pretty=format:%H|%s|%an|%ad|%h", "--date=short"],
                cwd=self.repo_root,
                capture_output=True,
                text=True,
                encoding='utf-8'
            )
            
            commits = []
            for line in result.stdout.strip().split('\n'):
                if line:
                    parts = line.split('|')
                    if len(parts) >= 5:
                        commits.append({
                            "hash": parts[0],
                            "short_hash": parts[4],
                            "message": parts[1],
                            "author": parts[2],
                            "date": parts[3]
                        })
            
            return commits
        except Exception:
            return []
    
    def get_all_commits(self) -> List[Dict[str, str]]:
        """Get all commits for version analysis."""
        try:
            result = subprocess.run(
                ["git", "log", "--pretty=format:%H|%s|%an|%ad|%h", "--date=short"],
                cwd=self.repo_root,
                capture_output=True,
                text=True,
                encoding='utf-8'
            )
            
            commits = []
            for line in result.stdout.strip().split('\n'):
                if line:
                    parts = line.split('|')
                    if len(parts) >= 5:
                        commits.append({
                            "hash": parts[0],
                            "short_hash": parts[4],
                            "message": parts[1],
                            "author": parts[2],
                            "date": parts[3]
                        })
            
            return commits
        except Exception:
            return []
    
    def get_contributors(self) -> List[Dict[str, int]]:
        """Get contributors sorted by commit count."""
        try:
            result = subprocess.run(
                ["git", "shortlog", "-sn", "--all"],
                cwd=self.repo_root,
                capture_output=True,
                text=True,
                encoding='utf-8'
            )
            
            contributors = []
            for line in result.stdout.strip().split('\n'):
                if line:
                    match = re.match(r'^\s*(\d+)\s+(.+)$', line)
                    if match:
                        contributors.append({
                            "name": match.group(2),
                            "commits": int(match.group(1))
                        })
            
            return contributors
        except Exception:
            return []
    
    def get_total_commit_count(self) -> int:
        """Get total number of commits."""
        try:
            result = subprocess.run(
                ["git", "rev-list", "--count", "HEAD"],
                cwd=self.repo_root,
                capture_output=True,
                text=True,
                encoding='utf-8'
            )
            return int(result.stdout.strip())
        except Exception:
            return 0
    
    def get_repo_url(self) -> Optional[str]:
        """Get the repository URL."""
        try:
            result = subprocess.run(
                ["git", "remote", "get-url", "origin"],
                cwd=self.repo_root,
                capture_output=True,
                text=True,
                encoding='utf-8'
            )
            
            url = result.stdout.strip()
            # Convert SSH URL to HTTPS
            if url.startswith("git@"):
                url = url.replace("git@github.com:", "https://github.com/")
                url = url.replace(".git", "")
            return url
        except Exception:
            return None


class ReadmeGenerator:
    """Generates the README content."""
    
    def __init__(self, project_root: Path):
        self.project_root = project_root
        self.stats = ProjectStats(project_root)
        self.git = GitInfo(project_root)
        self.version_manager = VersionManager(project_root)
        self.copyright_manager = CopyrightManager(project_root)
    
    def generate(self) -> str:
        """Generate the complete README content."""
        # Gather all data
        uproject = self.stats.get_uproject_info()
        cpp_stats = self.stats.count_cpp_files()
        loc_stats = self.stats.count_lines_of_code()
        classes = self.stats.get_class_list()
        tags = self.stats.get_gameplay_tags()
        commits = self.git.get_recent_commits(10)
        all_commits = self.git.get_all_commits()
        contributors = self.git.get_contributors()
        repo_url = self.git.get_repo_url()
        total_commits = self.git.get_total_commit_count()
        copyright_summary = self.copyright_manager.get_copyright_summary()
        
        # Get version info
        version_info = self.version_manager.get_version_info(all_commits)
        
        # Build README sections
        readme = self._build_header(uproject, version_info)
        readme += self._build_badges(uproject, version_info)
        readme += self._build_version_section(version_info)
        readme += self._build_description(uproject)
        readme += self._build_stats_section(cpp_stats, loc_stats, contributors, total_commits, version_info)
        readme += self._build_copyright_section(copyright_summary)
        readme += self._build_directory_structure()
        readme += self._build_classes_section(classes)
        readme += self._build_gameplay_tags_section(tags)
        readme += self._build_recent_commits(commits, repo_url)
        readme += self._build_contributors_section(contributors)
        readme += self._build_footer(copyright_summary)
        
        return readme
    
    def _build_header(self, uproject: Dict, version_info: Dict) -> str:
        """Build the README header."""
        name = uproject.get("name", "DA")
        stage = version_info.get("stage", "pre-alpha")
        version = version_info.get("version_string", "0.1.0")
        
        # Stage emoji
        stage_emoji = {
            "pre-alpha": " embryo",
            "alpha": " alpha",
            "beta": " beta",
            "rc": " rc",
            "stable": ""
        }.get(stage, "")
        
        return f"""# {name}

> An Unreal Engine {uproject.get('engine', '5.x')} Project | Version {version}{stage_emoji}

"""
    
    def _build_badges(self, uproject: Dict, version_info: Dict) -> str:
        """Build the badges section."""
        engine = uproject.get("engine", "5.3")
        version = version_info.get("version_string", "0.1.0")
        stage = version_info.get("stage", "pre-alpha")
        build = version_info.get("build", 1)
        
        # Stage color
        stage_color = {
            "pre-alpha": "lightgrey",
            "alpha": "orange",
            "beta": "yellow",
            "rc": "blue",
            "stable": "brightgreen"
        }.get(stage, "lightgrey")
        
        return f"""<!-- BADGES_START -->
[![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-{engine}-0EBEED?logo=unrealengine&logoColor=white)](https://www.unrealengine.com/)
[![Version](https://img.shields.io/badge/Version-{version}-{stage_color})]()
[![Stage](https://img.shields.io/badge/Stage-{stage}-{stage_color})]()
[![Build](https://img.shields.io/badge/Build-{build}-blue)]()
[![C++](https://img.shields.io/badge/C++-17-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
<!-- BADGES_END -->

"""
    
    def _build_version_section(self, version_info: Dict) -> str:
        """Build the version information section."""
        stage = version_info.get("stage", "pre-alpha")
        version = version_info.get("version_string", "0.1.0")
        build = version_info.get("build", 1)
        stats = version_info.get("stats", {})
        
        # Stage description
        stage_descriptions = {
            "pre-alpha": "Active development, features being implemented",
            "alpha": "Core features complete, testing in progress",
            "beta": "Feature complete, bug fixing and polish",
            "rc": "Release candidate, final testing",
            "stable": "Production ready"
        }
        
        stage_desc = stage_descriptions.get(stage, "Development in progress")
        
        return f"""<!-- VERSION_START -->
## Version Information

| Property | Value |
|----------|-------|
| **Version** | `{version}` |
| **Stage** | `{stage}` |
| **Build** | `{build}` |
| **Full Version** | `{version_info.get('full_version', version)}` |

### Development Progress

{stage_desc}

| Metric | Count |
|--------|-------|
| Breaking Changes | {stats.get('breaking_changes', 0)} |
| New Features | {stats.get('new_features', 0)} |
| Bug Fixes | {stats.get('bug_fixes', 0)} |
| Other Changes | {stats.get('other_changes', 0)} |

<!-- VERSION_END -->

"""
    
    def _build_description(self, uproject: Dict) -> str:
        """Build the description section."""
        description = uproject.get("description", "")
        
        content = """## Overview

<!-- DESCRIPTION_START -->
"""
        if description:
            content += f"{description}\n"
        else:
            content += """DA is an Unreal Engine project featuring a comprehensive Gameplay Ability System (GAS) with 
custom attributes (Health, Stamina, Mana), character mechanics, and modular architecture designed for extensibility.

### Key Features

- Gameplay Ability System - Full GAS integration with custom ability system component
- Attribute System - Replicated attributes for Health, Stamina, and Mana
- Character Classes - Flexible character class system with data-driven configuration
- State Tree - AI and gameplay logic using Unreal's StateTree plugin
- Modular Architecture - Clean separation of systems for maintainability
<!-- DESCRIPTION_END -->

"""
        return content
    
    def _build_stats_section(self, cpp_stats: Dict, loc_stats: Dict, contributors: List, total_commits: int, version_info: Dict) -> str:
        """Build the project statistics section."""
        total_contributors = len(contributors)
        
        return f"""<!-- STATS_START -->
## Project Statistics

| Metric | Count |
|--------|-------|
| Header Files | {cpp_stats['headers']} |
| Source Files | {cpp_stats['sources']} |
| Total C++ Files | {cpp_stats['total']} |
| Total Lines | {loc_stats['total_lines']:,} |
| Code Lines | {loc_stats['code_lines']:,} |
| Comment Lines | {loc_stats['comment_lines']:,} |
| Total Commits | {total_commits} |
| Contributors | {total_contributors} |

<!-- STATS_END -->

"""
    
    def _build_copyright_section(self, copyright_summary: Dict) -> str:
        """Build the copyright section."""
        holders = copyright_summary.get("copyright_holders", [])
        copyright_string = copyright_summary.get("copyright_string", "")
        
        holders_list = ", ".join(holders) if holders else "RaioCore, Raioix"
        
        return f"""<!-- COPYRIGHT_START -->
## Copyright

{copyright_string}

### Copyright Holders

| Holder | Role |
|--------|------|
{self._format_copyright_holders(holders)}

### File Copyright Status

| Status | Count |
|--------|-------|
| Correct Copyright | {copyright_summary.get('files_with_correct_copyright', 0)} |
| Epic Games (Template) | {copyright_summary.get('files_with_epic_copyright', 0)} |
| Placeholder | {copyright_summary.get('files_with_placeholder', 0)} |
| Missing | {copyright_summary.get('files_without_copyright', 0)} |

<!-- COPYRIGHT_END -->

"""
    
    def _format_copyright_holders(self, holders: List[str]) -> str:
        """Format copyright holders as markdown table rows."""
        rows = []
        for holder in holders:
            rows.append(f"| {holder} | Project Owner |")
        return "\n".join(rows)
    
    def _build_directory_structure(self) -> str:
        """Build the directory structure section."""
        structure = self.stats.get_directory_structure()
        
        return f"""<!-- DIRECTORY_START -->
## Project Structure

```
{structure}
```

<!-- DIRECTORY_END -->

"""
    
    def _build_classes_section(self, classes: List[Dict]) -> str:
        """Build the C++ classes documentation section."""
        if not classes:
            return ""
        
        # Group classes by directory/module
        grouped = {}
        for cls in classes:
            module = cls['file'].split(os.sep)[1] if len(cls['file'].split(os.sep)) > 1 else "Core"
            if module not in grouped:
                grouped[module] = []
            grouped[module].append(cls)
        
        content = """<!-- CLASSES_START -->
## C++ Classes

"""
        
        for module, module_classes in sorted(grouped.items()):
            content += f"### {module}\n\n"
            content += "| Class | Type | Base | Description |\n"
            content += "|-------|------|------|-------------|\n"
            
            for cls in module_classes:
                base = cls.get('base') or '-'
                brief = cls.get('brief', '-')[:50] + ('...' if len(cls.get('brief', '')) > 50 else '')
                content += f"| `{cls['name']}` | {cls['type']} | `{base}` | {brief} |\n"
            
            content += "\n"
        
        content += "<!-- CLASSES_END -->\n\n"
        return content
    
    def _build_gameplay_tags_section(self, tags: List[str]) -> str:
        """Build the gameplay tags section."""
        if not tags:
            return ""
        
        content = """<!-- TAGS_START -->
## Gameplay Tags

"""
        
        # Group tags by category
        categories = {}
        for tag in tags:
            parts = tag.split('.')
            category = parts[0] if len(parts) > 1 else "General"
            if category not in categories:
                categories[category] = []
            categories[category].append(tag)
        
        for category, category_tags in sorted(categories.items()):
            content += f"### {category}\n"
            for tag in category_tags:
                content += f"- `{tag}`\n"
            content += "\n"
        
        content += "<!-- TAGS_END -->\n\n"
        return content
    
    def _build_recent_commits(self, commits: List[Dict], repo_url: Optional[str]) -> str:
        """Build the recent commits section."""
        if not commits:
            return ""
        
        content = """<!-- COMMITS_START -->
## Recent Changes

"""
        
        for commit in commits[:10]:
            message = commit['message'][:60] + ('...' if len(commit['message']) > 60 else '')
            if repo_url:
                content += f"- [`{commit['short_hash']}`]({repo_url}/commit/{commit['hash']}) {message} ({commit['date']})\n"
            else:
                content += f"- `{commit['short_hash']}` {message} ({commit['date']})\n"
        
        content += "\n<!-- COMMITS_END -->\n\n"
        return content
    
    def _build_contributors_section(self, contributors: List[Dict]) -> str:
        """Build the contributors section."""
        if not contributors:
            return ""
        
        content = """<!-- CONTRIBUTORS_START -->
## Contributors

"""
        
        for contributor in contributors[:10]:
            content += f"- **{contributor['name']}** ({contributor['commits']} commits)\n"
        
        content += "\n<!-- CONTRIBUTORS_END -->\n\n"
        return content
    
    def _build_footer(self, copyright_summary: Dict) -> str:
        """Build the README footer."""
        timestamp = datetime.now(timezone.utc).strftime("%Y-%m-%d %H:%M:%S UTC")
        copyright_string = copyright_summary.get("copyright_string", "Copyright 2026 RaioCore and Raioix. All Rights Reserved.")
        
        return f"""---

<p align="center">
  <i>{copyright_string}</i><br><br>
  <i>Last updated: {timestamp}</i><br>
  <i>This README is automatically generated from project files and git history.</i><br>
  <i>Version follows semantic versioning based on conventional commits.</i>
</p>
"""


def main():
    """Main entry point."""
    # Get project root (parent of scripts directory)
    script_dir = Path(__file__).parent
    project_root = script_dir.parent
    
    print(f"Generating README for: {project_root}")
    
    # Initialize managers
    copyright_manager = CopyrightManager(project_root)
    
    # Update source file headers with correct copyright
    print("Updating copyright headers in source files...")
    updated_files = copyright_manager.update_source_file_headers()
    print(f"Updated {updated_files} files with correct copyright headers")
    
    # Generate README
    generator = ReadmeGenerator(project_root)
    readme_content = generator.generate()
    
    # Write README
    readme_path = project_root / "README.md"
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(readme_content)
    
    print(f"README generated: {readme_path}")
    print(f"Size: {len(readme_content)} characters")


if __name__ == "__main__":
    main()
