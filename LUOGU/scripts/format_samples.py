import re, os, glob

files = glob.glob('*_data.txt')
for f in files:
    pid = f.replace('_data.txt', '')
    print(f'Fixing samples for {pid}...')
    
    with open(f, 'r', encoding='utf-8') as fp:
        content = fp.read()

    samples_section = re.search(r'=== Samples ===\n(.*?)=== Limits ===', content, re.DOTALL)
    if not samples_section:
        continue
        
    raw_samples = samples_section.group(1)
    # Split by '--- Sample X ---'
    sample_blocks = re.split(r'--- Sample \d+ ---\n', raw_samples)
    sample_blocks = [s.strip() for s in sample_blocks if s.strip()]
    
    formatted_samples = ''
    for i, block in enumerate(sample_blocks):
        lines = block.split('\n')
        in_input = False
        in_output = False
        input_lines = []
        output_lines = []
        
        for line in lines:
            if line.startswith('Input:'):
                in_input = True
                in_output = False
                continue
            elif line.startswith('Output:'):
                in_input = False
                in_output = True
                continue
            
            if in_input:
                input_lines.append(line)
            elif in_output:
                output_lines.append(line)
                
        formatted_samples += f'**输入样例 {i+1}**\n```\n' + "\n".join(input_lines) + f'\n```\n**输出样例 {i+1}**\n```\n' + "\n".join(output_lines) + f'\n```\n\n'

    md_file = f'{pid}.md'
    if os.path.exists(md_file):
        with open(md_file, 'r', encoding='utf-8') as fp:
            md_content = fp.read()
            
        # Use a unique marker to replace the samples block
        new_md = re.sub(r'## 样例\n\n', f'## 样例\n\n{formatted_samples}', md_content)
        
        with open(md_file, 'w', encoding='utf-8') as fp:
            fp.write(new_md)
