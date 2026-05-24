#!/usr/bin/env python3
"""
Android CLI Docs Tool Wrapper for Agent Skills Framework.
Conforms to the agentskills.io script invocation protocol.
"""

import sys
import subprocess
import shutil
import json

def check_env():
    """Validates if the underlying android binary is installed on the host."""
    return shutil.which("android") is not None

def run_search(query: str):
    """Executes the android docs search sequence."""
    if not query.strip():
        print("[ERROR] Search query cannot be empty.")
        sys.exit(1)

    print(f"[*] Querying Android CLI Knowledge Base for: '{query}'...")
    
    if not check_env():
        # Fallback simulation if execution happens in a decoupled bootstrap phase
        print("[WARN] 'android' CLI utility not detected in PATH. Emulating fallback lookup...")
        mock_results = {
            "compose": ["kb://framework/ui/compose/performance", "kb://framework/ui/compose/lazy-column"],
            "service": ["kb://framework/core/app/service-background-limits"],
            "aidl": ["kb://ndk/ipc/aidl-backend-bindings"]
        }
        
        query_lower = query.lower()
        found = False
        for key, paths in mock_results.items():
            if key in query_lower:
                found = True
                print("\nFound matching authoritative references:")
                for path in paths:
                    print(f"  - {path}")
        if not found:
            print("\n[INFO] No local documentation matches found for this query in mock index.")
        return

    try:
        # Invoke standard structural Android CLI interface
        result = subprocess.run(
            ["android", "docs", "search", query],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            check=True
        )
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"[ERROR] Failed to search index. Process exited with code {e.returncode}")
        print(e.stderr)
        sys.exit(1)

def run_fetch(uri: str):
    """Retrieves document payloads for a specific kb:// reference target."""
    if not uri.startswith("kb://"):
        print("[ERROR] Invalid URI format. Must begin with 'kb://'")
        sys.exit(1)

    print(f"[*] Fetching authoritative resource from source: {uri}")
    
    if not check_env():
        print("[WARN] 'android' CLI utility missing. Displaying structural template alternative:")
        print(f"--- Document Content for {uri} ---")
        print("// Reference structural example pattern. Run 'android update' to populate authentic local bytes.")
        print("public class ComponentPolicy { /* Stub Content Only */ }")
        return

    try:
        result = subprocess.run(
            ["android", "docs", "fetch", uri],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            check=True
        )
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"[ERROR] Failed to pull document payload. Process exited with code {e.returncode}")
        print(e.stderr)
        sys.exit(1)

def print_status():
    """Prints diagnostic system telemetry data back to the driving agent context."""
    has_cli = check_env()
    status_report = {
        "status": "READY" if has_cli else "DEGRADED_MOCK_FALLBACK",
        "android_cli_available": has_cli,
        "runtime_version": sys.version.split()[0],
        "target_specification": "agentskills.io/specification@2026"
    }
    print(json.dumps(status_report, indent=2))

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 doc_tool.py [search|fetch|status] [args...]")
        sys.exit(1)

    action = sys.argv[1].lower()

    if action == "search":
        if len(sys.argv) < 3:
            print("[ERROR] Missing query string parameter.")
            sys.exit(1)
        run_search(sys.argv[2])
    elif action == "fetch":
        if len(sys.argv) < 3:
            print("[ERROR] Missing target kb:// URI identifier.")
            sys.exit(1)
        run_fetch(sys.argv[2])
    elif action == "status":
        print_status()
    else:
        print(f"[ERROR] Unsupported script action rule parameter: {action}")
        sys.exit(1)

if __name__ == "__main__":
    main()
